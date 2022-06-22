package io.quaker762.github.smb3;

import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.util.*;
import javax.imageio.ImageIO;
import javax.swing.*;
import javax.swing.GroupLayout.Alignment;
import javax.swing.LayoutStyle.ComponentPlacement;
import javax.swing.border.EmptyBorder;
import javax.swing.border.EtchedBorder;
import javax.swing.border.TitledBorder;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;

import io.quaker762.github.smb3.*;

public class AGFEd extends JFrame implements ActionListener {
	
	private static final long serialVersionUID = 1041077314614097175L;
	
	private SheetView sheetViewer;
	private ArrayList<Animation> animations;
	private Animation currentAnimation;
	
	private JMenuItem loadSheetItem;
	private JList<String> animationList;
	private JList<String> frameList;
	
	private JButton newAnimationButton;
	private JButton removeFrameButton;
	
	private DefaultListModel<String> animationListModel;
	private DefaultListModel<String> frameListModel;
	
	public AGFEd()
	{
	    super("AGFEd");

	    currentAnimation = null;
	    
	    // Create the animations array list
	    animations = new ArrayList<Animation>();
	    
	    setSize(1024, 768);
	    setResizable(false);
	    Dimension screen_size = Toolkit.getDefaultToolkit().getScreenSize();
	    setLocation((screen_size.width - getWidth()) / 2, (screen_size.height - getHeight()) / 2);
	    setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	    
	    newAnimationButton = new JButton("New Animation");
	    newAnimationButton.addActionListener(this);
	    removeFrameButton = new JButton("Delete Frame");
	    removeFrameButton.addActionListener(this); 

	    animationListModel = new DefaultListModel();
	    animationList = new JList<String>(animationListModel);
	    frameListModel = new DefaultListModel();
	    frameList = new JList<String>(frameListModel);
	    
	    JPanel widgetPanel = new JPanel();
	    widgetPanel.setLayout(new BoxLayout(widgetPanel, BoxLayout.Y_AXIS));
	    JPanel animationListPanel = new JPanel(new BorderLayout());
	    animationListPanel.add(BorderLayout.CENTER, new JScrollPane(animationList));
	    animationListPanel.add(BorderLayout.SOUTH, newAnimationButton);
	    animationListPanel.setBorder(new TitledBorder(new EtchedBorder(), "Animations"));
	    widgetPanel.add(animationListPanel);

	    JPanel animationFramePanel = new JPanel(new BorderLayout());
	    animationFramePanel.add(BorderLayout.CENTER, new JScrollPane(frameList));
	    animationFramePanel.add(BorderLayout.SOUTH, removeFrameButton);
	    animationFramePanel.setBorder(new TitledBorder(new EtchedBorder(), "Frames"));
        widgetPanel.add(animationFramePanel);
	        
	    setJMenuBar(buildMenuBarPanel());
	    
        sheetViewer = new SheetView(frameListModel);
	    
	    JPanel mainPanel = new JPanel(new BorderLayout());
	    mainPanel.add(BorderLayout.WEST, widgetPanel);
	    mainPanel.add(BorderLayout.CENTER, new JScrollPane(sheetViewer));
	    
	    setContentPane(mainPanel);
	    
	    animationList.addListSelectionListener(new ListSelectionListener()
	    {
	        @Override
            public void valueChanged(ListSelectionEvent e)
            {
                int selectedIndex = animationList.getSelectedIndex();
                if (selectedIndex >= 0)
                {
                    currentAnimation = animations.get(selectedIndex);
                    sheetViewer.setCurrentAnimation(currentAnimation);
                    frameListModel.clear();
                    for (int i = 0; i < currentAnimation.frameCount(); i++)
                    {
                        frameListModel.addElement("Frame " + i);
                    }
                }

                sheetViewer.repaint();
            }
	    });
	    
	    animationList.addMouseListener(new MouseListener() 
	    {
            @Override
            public void mouseClicked(MouseEvent e)
            {
                if (e.getButton() == MouseEvent.BUTTON3)
                {
                    // Don't show the menu if nothing is selected
                    if (animationList.getSelectedIndex() < 0)
                    {
                        return;
                    }
                    
                    JPopupMenu menu = new JPopupMenu("Animation");
                    JMenuItem parametersItem = new JMenuItem("Animation Parameters");
                    menu.add(parametersItem);
                    menu.setLocation(e.getX(), e.getY());
                    menu.show(animationList, e.getX(), e.getY());
                    
                    parametersItem.addActionListener(new ActionListener() 
                    {
                        @Override
                        public void actionPerformed(ActionEvent e)
                        {
                            JFrame frame = new JFrame();
                            JPanel contentPane = new JPanel();
                            contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
                            frame.setContentPane(contentPane);
                            
                            JLabel lblTicksPerFrame = new JLabel("Ticks Per Frame");
                            JSpinner ticksPerFrame = new JSpinner();
                            JLabel lblFrameWidth = new JLabel("Frame Width");
                            JSpinner frameWidth = new JSpinner();
                            JLabel lblFrameHeight = new JLabel("Frame Height");
                            JSpinner frameHeight = new JSpinner();
                            
                            JButton saveButton = new JButton("Save");
                            saveButton.addActionListener(new ActionListener()
                            {
                                public void actionPerformed(ActionEvent e)
                                {
                                    int frameWidthVal   = Integer.parseInt(frameWidth.getValue().toString());
                                    int frameHeightVal  = Integer.parseInt(frameHeight.getValue().toString());
                                    int ticksPerFrameVal = Integer.parseInt(ticksPerFrame.getValue().toString());
                                    if ((frameWidthVal % 2) != 0)
                                    {
                                        JOptionPane.showMessageDialog(frame, "Frame width must be divisible by 2!", "Error", JOptionPane.ERROR_MESSAGE);
                                        return;
                                    }
                                    else if ((frameHeightVal % 2) != 0)
                                    {
                                        JOptionPane.showMessageDialog(frame, "Frame height must be divisible by 2!", "Error", JOptionPane.ERROR_MESSAGE);
                                        return;
                                    }
                                    else if (ticksPerFrameVal <= 0)
                                    {
                                        JOptionPane.showMessageDialog(frame, "Ticks per frame cannot be less than or equal to zero!", "Error", JOptionPane.ERROR_MESSAGE);
                                        return;
                                    }
                                    else if ((frameWidthVal <= 0) || (frameHeightVal <= 0))
                                    {
                                        JOptionPane.showMessageDialog(frame, "Frame width and height must be greater than zero!", "Error", JOptionPane.ERROR_MESSAGE);
                                        return;
                                    }
                                    else if (frameWidthVal >= Byte.MAX_VALUE)
                                    {
                                        JOptionPane.showMessageDialog(frame, "Frame width cannot exeed 255!", "Error", JOptionPane.ERROR_MESSAGE);
                                    }
                                    else if (frameHeightVal >= Byte.MAX_VALUE)
                                    {
                                        JOptionPane.showMessageDialog(frame, "Frame height cannot exeed 255!", "Error", JOptionPane.ERROR_MESSAGE);
                                    }
                                    else if (ticksPerFrameVal >= Short.MAX_VALUE)
                                    {
                                        JOptionPane.showMessageDialog(frame, "Ticks per frame cannot exceed " + Short.MAX_VALUE, "Error", JOptionPane.ERROR_MESSAGE);
                                    }
                                    
                                    if (currentAnimation != null)
                                    {
                                        currentAnimation.setFrameWidth((byte)frameWidthVal);
                                        currentAnimation.setFrameHeight((byte)frameHeightVal);
                                        currentAnimation.setTicksPerFrame((byte)ticksPerFrameVal);
                                    }
                                    
                                    frame.setVisible(false);
                                }
                            });
                            
                            JButton cancelButton = new JButton("Cancel");
                            cancelButton.addActionListener(new ActionListener()
                            {
                                @Override
                                public void actionPerformed(ActionEvent e)
                                {
                                    frame.setVisible(false);
                                }
                            });
                            
                            GroupLayout gl_contentPane = new GroupLayout(contentPane);
                            gl_contentPane.setHorizontalGroup(
                                    gl_contentPane.createParallelGroup(Alignment.TRAILING)
                                        .addGroup(gl_contentPane.createSequentialGroup()
                                            .addContainerGap()
                                            .addGroup(gl_contentPane.createParallelGroup(Alignment.LEADING)
                                                .addGroup(gl_contentPane.createSequentialGroup()
                                                    .addComponent(lblTicksPerFrame)
                                                    .addPreferredGap(ComponentPlacement.RELATED)
                                                    .addComponent(ticksPerFrame, GroupLayout.DEFAULT_SIZE, 51, Short.MAX_VALUE))
                                                .addGroup(gl_contentPane.createSequentialGroup()
                                                    .addComponent(lblFrameWidth, GroupLayout.PREFERRED_SIZE, 99, GroupLayout.PREFERRED_SIZE)
                                                    .addPreferredGap(ComponentPlacement.RELATED)
                                                    .addComponent(frameWidth, GroupLayout.DEFAULT_SIZE, 51, Short.MAX_VALUE))
                                                .addGroup(gl_contentPane.createSequentialGroup()
                                                    .addComponent(lblFrameHeight, GroupLayout.PREFERRED_SIZE, 99, GroupLayout.PREFERRED_SIZE)
                                                    .addPreferredGap(ComponentPlacement.RELATED)
                                                    .addComponent(frameHeight, GroupLayout.DEFAULT_SIZE, 51, Short.MAX_VALUE))
                                                .addGroup(gl_contentPane.createSequentialGroup()
                                                    .addComponent(cancelButton)
                                                    .addPreferredGap(ComponentPlacement.RELATED)
                                                    .addComponent(saveButton)))
                                            .addContainerGap())
                                );
                                gl_contentPane.setVerticalGroup(
                                    gl_contentPane.createParallelGroup(Alignment.LEADING)
                                        .addGroup(gl_contentPane.createSequentialGroup()
                                            .addContainerGap()
                                            .addGroup(gl_contentPane.createParallelGroup(Alignment.BASELINE)
                                                .addComponent(lblTicksPerFrame)
                                                .addComponent(ticksPerFrame, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE))
                                            .addGroup(gl_contentPane.createParallelGroup(Alignment.LEADING)
                                                .addGroup(gl_contentPane.createSequentialGroup()
                                                    .addGap(14)
                                                    .addComponent(lblFrameWidth))
                                                .addGroup(gl_contentPane.createSequentialGroup()
                                                    .addPreferredGap(ComponentPlacement.UNRELATED)
                                                    .addComponent(frameWidth, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE)))
                                            .addPreferredGap(ComponentPlacement.UNRELATED)
                                            .addGroup(gl_contentPane.createParallelGroup(Alignment.BASELINE)
                                                .addComponent(lblFrameHeight)
                                                .addComponent(frameHeight, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE))
                                            .addPreferredGap(ComponentPlacement.UNRELATED)
                                            .addGroup(gl_contentPane.createParallelGroup(Alignment.BASELINE)
                                                .addComponent(cancelButton)
                                                .addComponent(saveButton))
                                            .addContainerGap(GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
                                );
                            contentPane.setLayout(gl_contentPane);
                            frame.setBounds(100, 100, 206, 187);
                            frame.setLocationRelativeTo(sheetViewer);
                            frame.setVisible(true);
                        }
                    });
                }
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
	    });
	    
	    frameList.addListSelectionListener(new ListSelectionListener() 
	    {
            @Override
            public void valueChanged(ListSelectionEvent e)
            {
                int selectedIndex = frameList.getSelectedIndex();
                if (selectedIndex >= 0)
                {
                    sheetViewer.setCurrentFrameIndex(selectedIndex);
                }
                
                sheetViewer.repaint();
            }
	    });
	}
	
	public JMenuBar buildMenuBarPanel()
	{
	    JMenu fileMenu = new JMenu("File");
	    loadSheetItem = new JMenuItem("Load Sheet");
	    loadSheetItem.addActionListener(this);
	    
	    JMenuBar menuBar = new JMenuBar();
	    menuBar.add(fileMenu);
	    fileMenu.add(loadSheetItem);
	    
	    return menuBar;
	}

    public static void main(String[] args)
	{
		new AGFEd().setVisible(true);
	}

	@Override
	public void actionPerformed(ActionEvent e) 
	{
	    if (e.getSource() == loadSheetItem)
	    {
	        JFileChooser chooser = new JFileChooser();
	        chooser.setCurrentDirectory(new File("./"));
	        int result = chooser.showOpenDialog(this);
	        
	        if (result == JFileChooser.APPROVE_OPTION)
	        {
	            try
	            {
	                sheetViewer.setSheetImage(ImageIO.read(chooser.getSelectedFile()));
	                sheetViewer.repaint();
	            } 
	            catch (IOException e1)
	            {
	                // TODO Auto-generated catch block
	                e1.printStackTrace();
	            }
	        }
	    }
	    else if (e.getSource() == removeFrameButton)
	    {         
            int selectedFrameIndex = frameList.getSelectedIndex();
            if (selectedFrameIndex >= 0)
            {
                currentAnimation.removeFrameAt(selectedFrameIndex);
                frameListModel.clear();
                for (int i = 0; i < currentAnimation.frameCount(); i++)
                {
                    frameListModel.addElement("Frame " + i);
                }
                
                if (currentAnimation.frameCount() > 0)
                {
                    if ((selectedFrameIndex - 1) < 0)
                    {
                        frameList.setSelectedIndex(0);
                    }
                    else
                    {
                        frameList.setSelectedIndex(selectedFrameIndex - 1);
                    }
                }
                else if (currentAnimation.frameCount() == 0)
                {
                    frameList.setSelectedIndex(0);
                }
            
                sheetViewer.repaint();
            }
	    }
	    else if (e.getSource() == newAnimationButton)
	    {
	        Animation animation = new Animation();
	        animations.add(animation);
	        animationListModel.addElement("Animation " + (animations.size() - 1));
	        
	        animationList.setSelectedIndex(animations.size() - 1);
	    }
	}
}
