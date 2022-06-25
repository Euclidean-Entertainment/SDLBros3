package io.quaker762.github.smb3;

import java.io.*;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.file.Files;
import java.util.*;

import javax.swing.JOptionPane;

public class AGFDiskIO
{
    public static final String  AGF_FILE_EXTENSION = ".agf";
    private static final byte   FILE_HEADER_MAGIC[] = { 'S', 'M', 'B', 'A', 'N', 'M', '0', 0 };
    private static final byte   ANIMATION_HEADER_MAGIC[] = { 'A', 'D', 'H', 0 };
    private static final byte   AGF_VERSION_MAJOR = 0;
    private static final byte   AGF_VERSION_MINOR = 1;

    private static final int    FILE_HEADER_SIZE = 16;
    private static final int    ANIMATION_HEADER_SIZE = 6;
    private static final int    ANIMATION_SIZE = 6;
    
    private static void writeFileHeader(ByteBuffer agfStream, short animationCount) throws IOException
    {
        System.out.print("Writing AGF file header... ");
        agfStream.put(FILE_HEADER_MAGIC);
        agfStream.putShort(animationCount);
        agfStream.put(AGF_VERSION_MAJOR);
        agfStream.put(AGF_VERSION_MINOR);
        for (int i = 0; i < 4; i++)
        {
            agfStream.put((byte)0);
        }

        System.out.println("Done!");
    }
    
    private static void writeAnimationData(ByteBuffer agfStream, ArrayList<Animation> animations) throws IOException
    {
        // Write each animation out to disk
        System.out.print("Writing Animation Data... ");
        for (Animation animation : animations)
        {
            agfStream.put(ANIMATION_HEADER_MAGIC);
            agfStream.order(ByteOrder.LITTLE_ENDIAN);
            agfStream.put(animation.frameCount());
            agfStream.put(animation.ticksPerFrame());
            
            // Write each frame out to disk
            for (Frame frame : animation.frameList())
            {
                agfStream.putShort(frame.x);
                agfStream.putShort(frame.y);
                agfStream.put(frame.width);
                agfStream.put(frame.height);
            }
        }

        System.out.println("Done!");
    }
    
    private static Animation readAGFAnimation(ByteBuffer buffer)
    {
        Animation animation     = new Animation();
        byte[] animMagic        = new byte[4];
        byte frameCount         = 0;
        byte frameLength        = 0;
        
        buffer.get(animMagic);
        frameCount  = buffer.get();
        frameLength = buffer.get();
        
        if (Arrays.compare(animMagic, ANIMATION_HEADER_MAGIC) != 0)
        {
            JOptionPane.showMessageDialog(null, "Bad Animation Header Magic!", "Error", JOptionPane.ERROR_MESSAGE);
            return null;
        }
        
        for (int i = 0; i < frameCount; i++)
        {
            short sheetX        = buffer.getShort();
            short sheetY        = buffer.getShort();
            byte spriteWidth    = buffer.get();
            byte spriteHeight   = buffer.get();
            animation.addFrame(new Frame(sheetX, sheetY, spriteWidth, spriteHeight));
        }
        
        animation.setTicksPerFrame(frameLength);
        return animation;
    }

    private static short parseAGFHeader(ByteBuffer buffer)
    {
        byte[] magic            = new byte[8];
        byte[] reserved         = new byte[4];
        short agfAnimationCount = 0;
        byte agfVersionMajor    = 0;
        byte agfVersionMinor    = 0;
        
        buffer.get(magic);
        agfAnimationCount = buffer.getShort();
        agfVersionMajor = buffer.get();
        agfVersionMinor = buffer.get();
        buffer.get(reserved);
        if (Arrays.compare(magic, FILE_HEADER_MAGIC) != 0)
        {
            JOptionPane.showMessageDialog(null, "Bad AGF Magic!", "Error", JOptionPane.ERROR_MESSAGE);
            return 0;
        }
        
        if (agfAnimationCount == 0)
        {
            JOptionPane.showMessageDialog(null, "Animation count is zero!", "Error", JOptionPane.ERROR_MESSAGE);
            return 0;            
        }

        System.out.println("Number of animations: " + agfAnimationCount);
        System.out.println("AGF Version: " + agfVersionMajor + "." + agfVersionMinor);
        return agfAnimationCount;
    }
    
    private static ArrayList<Animation> parseAGF(ByteBuffer buffer)
    {
        ArrayList<Animation> animations = new ArrayList<Animation>();
        
        short animationCount = parseAGFHeader(buffer);
        if (animationCount == 0)
        {
            System.err.println("Invalid AGF header!");
            return null;
        }
        
        short currentAnimation;
        for (currentAnimation = 0; currentAnimation < animationCount; currentAnimation++)
        {
            Animation animation = readAGFAnimation(buffer);
            
            if (animation == null)
            {
                return null;
            }
            
            animations.add(animation);
        }
        
        if (currentAnimation != animationCount)
        {
            JOptionPane.showMessageDialog(null, "Animation read/count mismatch!", "Error", JOptionPane.ERROR_MESSAGE);
            return null;
        }
        
        return animations;
    }
    
    public static void saveAGF(ArrayList<Animation> animations, File file) throws IOException, FileNotFoundException
    {
        int bufferSize = FILE_HEADER_SIZE;
        
        for (int i = 0; i < animations.size(); i++)
        {
            bufferSize += ANIMATION_HEADER_SIZE;
            
            for (int j = 0; j < animations.get(i).frameCount(); j++)
            {
                bufferSize += ANIMATION_SIZE;
            }
        }
        
        System.out.println("Creating AGF file " + file.getAbsolutePath());

        ByteBuffer agfByteBuffer = ByteBuffer.allocate(bufferSize);
        agfByteBuffer.order(ByteOrder.LITTLE_ENDIAN);
        DataOutputStream agfStream = new DataOutputStream(new FileOutputStream(file));
        writeFileHeader(agfByteBuffer, (short)animations.size());
        writeAnimationData(agfByteBuffer, animations);
        agfStream.write(agfByteBuffer.array());
    }
    
    public static ArrayList<Animation> loadAGF(File file) throws IOException
    {
        ByteBuffer buffer = ByteBuffer.wrap(Files.readAllBytes(file.toPath()));
        buffer.order(ByteOrder.LITTLE_ENDIAN);
        
        return parseAGF(buffer);
    }
}
