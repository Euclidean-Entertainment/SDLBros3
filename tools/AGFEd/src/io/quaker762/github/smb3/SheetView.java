package io.quaker762.github.smb3;

import java.awt.*;
import java.awt.event.*;

import javax.swing.*;

public class SheetView extends JComponent implements MouseListener, MouseMotionListener
{
    private static final long serialVersionUID = 4906373392467366011L;
    
    private short       currX;
    private short       currY;
    private Image       sheetImage = null;
    private Animation   currentAnimation = null;
    private int         currentFrameIndex = 0;
    private boolean     showFrameNumbers = false;
    
    private DefaultListModel<String> frameDataModel;
    
    public SheetView(DefaultListModel<String> frameDataModel)
    {
        super();
        
        this.frameDataModel = frameDataModel;
        
        addMouseListener(this);
        addMouseMotionListener(this);
    }
    
    @Override
    public void paintComponent(Graphics g)
    {
        g.setColor(Color.BLACK);
        
        if (sheetImage != null)
        {
            g.drawImage(sheetImage, 0, 0, null);
        }
        
        if (currentAnimation != null)
        {
            int currentFrame = 0;
            for (Frame frame : currentAnimation.frameList())
            {
                g.setColor(Color.BLACK);
                if (currentFrameIndex == currentFrame)
                {
                    g.setColor(new Color(61, 227, 52));
                }
                g.drawRect(frame.x, frame.y, frame.width, frame.height);
                g.setColor(new Color(50, 168, 64));
                
                if (showFrameNumbers == true)
                {
                    g.drawString(Integer.toString(currentFrame), frame.x + 2, frame.y + 10);
                }
                
                currentFrame++;
            }
        }
       
        byte rectWidth = (currentAnimation != null) ? currentAnimation.frameWidth() : 16;
        byte rectHeight = (currentAnimation != null) ? currentAnimation.frameHeight() : 16;
        
        g.setColor(Color.BLACK);
        g.drawRect(currX * rectWidth, currY * rectHeight, rectWidth, rectHeight);
        g.drawString(Integer.toString((currentAnimation != null) ? currentAnimation.frameCount() : 0), currX * rectWidth + 2, currY * rectHeight + 10);
    }
    
    void setSheetImage(Image image)
    {
        sheetImage = image;
    }
    
    public void setCurrentAnimation(Animation animation)
    {
        this.currentAnimation = animation;
    }
    
    public void setCurrentFrameIndex(int frameIndex)
    {
        this.currentFrameIndex = frameIndex;
    }
    
    public void setShowFrameNumber(boolean showFrameNumbers)
    {
        this.showFrameNumbers = showFrameNumbers;
    }
    
    @Override
    public void mouseClicked(MouseEvent e)
    {
        if (currentAnimation == null)
        {
            return;
        }
        
        byte rectWidth = (currentAnimation != null) ? currentAnimation.frameWidth() : 16;
        byte rectHeight = (currentAnimation != null) ? currentAnimation.frameHeight() : 16;
        
        if (currentAnimation.frameCount() + 1 > Animation.MAX_FRAME_COUNT)
        {
            JOptionPane.showMessageDialog(this, "Frame count cannot exceed " + Animation.MAX_FRAME_COUNT, "Too many frames!", JOptionPane.ERROR_MESSAGE);
            return;
        }
        
        currentAnimation.addFrame(new Frame((short)(currX * rectWidth), (short)(currY * rectHeight), rectWidth, rectHeight));
        frameDataModel.addElement("Frame " + (currentAnimation.frameCount() - 1));
        repaint();
    }

    @Override
    public void mousePressed(MouseEvent e)
    {
    }

    @Override
    public void mouseReleased(MouseEvent e)
    {
    }

    @Override
    public void mouseEntered(MouseEvent e)
    {
    }

    @Override
    public void mouseExited(MouseEvent e)
    {
        
    }

    @Override
    public void mouseDragged(MouseEvent e)
    { 
    }

    @Override
    public void mouseMoved(MouseEvent e)
    {
        byte rectWidth = (currentAnimation != null) ? currentAnimation.frameWidth() : 16;
        byte rectHeight = (currentAnimation != null) ? currentAnimation.frameHeight() : 16;

        currX = (short) (e.getX() / rectWidth);
        currY = (short) (e.getY() / rectHeight);
        repaint();
    }
}
