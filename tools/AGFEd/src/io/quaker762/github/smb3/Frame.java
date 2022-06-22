package io.quaker762.github.smb3;

public class Frame
{
    public short    x;
    public short    y;
    public byte     width;
    public byte     height;
    
    public Frame()
    {
        this.x      = 0;
        this.y      = 0;
        this.width  = 0;
        this.height = 0;
    }
    
    public Frame(short x, short y, byte width, byte height)
    {
        this.x      = x;
        this.y      = y;
        this.width  = width;
        this.height = height;
    }
}
