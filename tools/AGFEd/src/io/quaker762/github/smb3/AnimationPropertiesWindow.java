package io.quaker762.github.smb3;

import java.awt.BorderLayout;
import java.awt.EventQueue;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;
import javax.swing.GroupLayout;
import javax.swing.GroupLayout.Alignment;
import javax.swing.JButton;
import javax.swing.LayoutStyle.ComponentPlacement;
import javax.swing.JLabel;
import javax.swing.JSpinner;

public class AnimationPropertiesWindow extends JFrame
{

    private static final long serialVersionUID = -3526923147694926792L;
    private JPanel contentPane;

    /**
     * Create the frame.
     */
    public AnimationPropertiesWindow()
    {
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setBounds(100, 100, 206, 187);
        contentPane = new JPanel();
        contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
        setContentPane(contentPane);
        
        JButton saveButton = new JButton("Save");
        JButton cancelButton = new JButton("Cancel");
        JLabel lblTicksPerFrame = new JLabel("Ticks Per Frame");
        JSpinner ticksPerFrame = new JSpinner();
        JLabel lblFrameWidth = new JLabel("Frame Width");
        JSpinner frameWidth = new JSpinner();
        JLabel lblFrameHeight = new JLabel("Frame Height");
        JSpinner frameHeight = new JSpinner();
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
    }
}
