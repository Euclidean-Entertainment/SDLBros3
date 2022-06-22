package io.quaker762.github.smb3;

import java.io.*;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.util.*;

public class AGFExport
{
    public static final String AGF_FILE_EXTENSION = ".agf";
    private static final byte   FILE_HEADER_MAGIC[] = { 'S', 'M', 'B', 'A', 'N', 'M', 0 };
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
}
