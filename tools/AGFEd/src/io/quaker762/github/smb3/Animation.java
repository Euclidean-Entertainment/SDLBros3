package io.quaker762.github.smb3;

import java.util.ArrayList;
import io.quaker762.github.smb3.Frame;

public class Animation extends Object
{
    static final private byte DEFAULT_FRAME_WIDTH       = 16;
    static final private byte DEFAULT_FRAME_HEIGHT      = 16;
    static final private byte DEFAULT_TICKS_PER_FRAME   = 4;
    
    public static final int MAX_FRAME_COUNT = 255;
    
    private ArrayList<Frame> frames;
    private String name;
    
    private byte frameWidth;
    private byte frameHeight;
    private byte ticksPerFrame;
    
    public Animation()
    {
        frames = new ArrayList<Frame>();
        
        frameWidth      = DEFAULT_FRAME_WIDTH;
        frameHeight     = DEFAULT_FRAME_HEIGHT;
        ticksPerFrame   = DEFAULT_TICKS_PER_FRAME;
    }
    
    public ArrayList<Frame> frameList()
    {
        return frames;
    }
    
    public void setName(String name)
    {
        this.name = name;
    }
    
    public String getName()
    {
        return name;
    }
    
    public void addFrame(Frame frame)
    {
        frames.add(frame);
    }
    
    public int frameCount()
    {
        return frames.size();
    }
    
    public void removeFrameAt(int frame)
    {
        frames.remove(frame);
    }
    
    public Frame frameAt(int frame)
    {
        assert(frame < frames.size());
        return frames.get(frame);
    }
    
    public byte frameWidth()
    {
        return frameWidth;
    }
    
    public byte frameHeight()
    {
        return frameHeight;
    }
    
    public byte ticksPerFrame()
    {
        return ticksPerFrame;
    }
    
    public void setFrameWidth(byte width)
    {
        this.frameWidth = width;
    }
    
    public void setFrameHeight(byte height)
    {
        this.frameHeight = height;
    }
    
    public void setTicksPerFrame(byte ticksPerFrame)
    {
        this.ticksPerFrame = ticksPerFrame;
    }
}
