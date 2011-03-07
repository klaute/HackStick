package vu.de.klaute.view;
import java.awt.BorderLayout;
import java.awt.FlowLayout;
import java.awt.GridLayout;

import javax.swing.*;
import javax.swing.border.BevelBorder;
import javax.swing.border.LineBorder;

/**
* This code was edited or generated using CloudGarden's Jigloo
* SWT/Swing GUI Builder, which is free for non-commercial
* use. If Jigloo is being used commercially (ie, by a corporation,
* company or business for any purpose whatever) then you
* should purchase a license for each developer using Jigloo.
* Please visit www.cloudgarden.com for details.
* Use of Jigloo implies acceptance of these licensing terms.
* A COMMERCIAL LICENSE HAS NOT BEEN PURCHASED FOR
* THIS MACHINE, SO JIGLOO OR THIS CODE CANNOT BE USED
* LEGALLY FOR ANY CORPORATE OR COMMERCIAL PURPOSE.
*/
public class HSSDUI extends javax.swing.JFrame {

	/**
	 * 
	 */
	private static final long serialVersionUID = -1183701661007811521L;
	private JMenuItem helpMenuItem;
	private JTree jTree1;
	private JMenu jMenu5;
	private JLabel jLabel3;
	private JTextField jTextField1;
	private JSeparator jSeparator1;
	private JPanel jPanel4;
	private JTextField jTextField4;
	private JLabel jLabel7;
	private JLabel jLabel6;
	private JTextField jTextField3;
	private JLabel jLabel5;
	private JTextField jTextField2;
	private JLabel jLabel4;
	private JLabel jLabel2;
	private JComboBox jComboBox1;
	private JLabel jLabel1;
	private JPanel jPanel3;
	private JPanel jPanel1;
	private JMenuItem exitMenuItem;
	private JSeparator jSeparator2;
	private JMenuItem closeFileMenuItem;
	private JMenuItem saveAsMenuItem;
	private JMenuItem saveMenuItem;
	private JScrollPane jScrollPane1;
	private JTextArea jTextArea1;
	private JPanel jPanel2;
	private JMenuItem openFileMenuItem;
	private JMenuItem newFileMenuItem;
	private JMenu jMenu3;
	private JMenuBar jMenuBar1;

	/**
	* Auto-generated main method to display this JFrame
	*/
	public static void main(String[] args) {
		SwingUtilities.invokeLater(new Runnable() {
			public void run() {
				HSSDUI inst = new HSSDUI();
				inst.setLocationRelativeTo(null);
				inst.setVisible(true);
			}
		});
	}
	
	public HSSDUI() {
		super();
		initGUI();
	}
	
	private void initGUI() {
		try {
			{
				jPanel1 = new JPanel();
				getContentPane().add(jPanel1);
				/*FormLayout jPanel1Layout = new FormLayout(
						"max(p;5dlu), max(p;5dlu), max(p;5dlu), max(p;5dlu)", 
						"max(p;5dlu), max(p;5dlu), max(p;5dlu), max(p;5dlu)");*/
						GroupLayout jPanel1Layout1 = new GroupLayout((JComponent)jPanel1);
						jPanel1.setLayout(jPanel1Layout1);
						jPanel1.setPreferredSize(new java.awt.Dimension(754, 553));
						{
							jPanel4 = new JPanel();
							GroupLayout jPanel4Layout = new GroupLayout((JComponent)jPanel4);
							jPanel4.setLayout(jPanel4Layout);
							jPanel4.setBorder(BorderFactory.createEtchedBorder(BevelBorder.LOWERED));
							{
								jTree1 = new JTree();
								jTree1.setAutoscrolls(true);
							}
							jPanel4Layout.setHorizontalGroup(jPanel4Layout.createSequentialGroup()
								.addComponent(jTree1, 0, 186, Short.MAX_VALUE));
							jPanel4Layout.setVerticalGroup(jPanel4Layout.createSequentialGroup()
								.addComponent(jTree1, 0, 535, Short.MAX_VALUE));
						}
						{
							jPanel3 = new JPanel();
							GroupLayout jPanel3Layout = new GroupLayout((JComponent)jPanel3);
							jPanel3.setLayout(jPanel3Layout);
							jPanel3.setSize(630, 70);
							jPanel3.setBorder(BorderFactory.createEtchedBorder(BevelBorder.LOWERED));
							{
								jLabel1 = new JLabel();
								jLabel1.setText("Index:");
							}
							{
								ComboBoxModel jComboBox1Model = 
									new DefaultComboBoxModel(
											new String[] { "Item One", "Item Two" });
								jComboBox1 = new JComboBox();
								jComboBox1.setModel(jComboBox1Model);
							}
							{
								jLabel2 = new JLabel();
								jLabel2.setText("Value:");
							}
							{
								jSeparator1 = new JSeparator();
								jSeparator1.setOrientation(SwingConstants.VERTICAL);
							}
							{
								jTextField4 = new JTextField();
								jTextField4.setText("0x00");
							}
							{
								jLabel7 = new JLabel();
								jLabel7.setText("Allgemein:");
								jLabel7.setFont(new java.awt.Font("Dialog",1,12));
							}
							{
								jLabel6 = new JLabel();
								jLabel6.setText("Tupel:");
								jLabel6.setFont(new java.awt.Font("Dialog",1,12));
							}
							{
								jTextField3 = new JTextField();
								jTextField3.setText("0x0F");
							}
							{
								jLabel5 = new JLabel();
								jLabel5.setText("Delay zw. Blöcken (ms):");
							}
							{
								jLabel3 = new JLabel();
								jLabel3.setText("USB Data Report Länge:");
							}
							{
								jTextField1 = new JTextField();
								jTextField1.setText("0x00");
							}
							{
								jLabel4 = new JLabel();
								jLabel4.setText("Delay vor Start (ms):");
							}
							{
								jTextField2 = new JTextField();
								jTextField2.setText("0xFF");
							}
							jPanel3Layout.setHorizontalGroup(jPanel3Layout.createSequentialGroup()
									.addContainerGap()
									.addGroup(jPanel3Layout.createParallelGroup()
											.addGroup(GroupLayout.Alignment.LEADING, jPanel3Layout.createSequentialGroup()
													.addComponent(jLabel6, GroupLayout.PREFERRED_SIZE, GroupLayout.PREFERRED_SIZE, GroupLayout.PREFERRED_SIZE)
													.addGap(12))
													.addGroup(jPanel3Layout.createSequentialGroup()
															.addPreferredGap(jLabel6, jLabel1, LayoutStyle.ComponentPlacement.INDENT)
															.addGroup(jPanel3Layout.createParallelGroup()
																	.addGroup(GroupLayout.Alignment.LEADING, jPanel3Layout.createSequentialGroup()
																			.addComponent(jLabel1, GroupLayout.PREFERRED_SIZE, GroupLayout.PREFERRED_SIZE, GroupLayout.PREFERRED_SIZE)
																			.addGap(7))
																			.addComponent(jLabel2, GroupLayout.Alignment.LEADING, GroupLayout.PREFERRED_SIZE, 44, GroupLayout.PREFERRED_SIZE))))
																			.addGap(25)
																			.addGroup(jPanel3Layout.createParallelGroup()
																					.addGroup(GroupLayout.Alignment.LEADING, jPanel3Layout.createSequentialGroup()
																							.addComponent(jTextField4, GroupLayout.PREFERRED_SIZE, 39, GroupLayout.PREFERRED_SIZE)
																							.addGap(40))
																							.addComponent(jComboBox1, GroupLayout.Alignment.LEADING, GroupLayout.PREFERRED_SIZE, GroupLayout.PREFERRED_SIZE, GroupLayout.PREFERRED_SIZE))
																							.addGap(17)
																							.addComponent(jSeparator1, GroupLayout.PREFERRED_SIZE, 10, GroupLayout.PREFERRED_SIZE)
																							.addGroup(jPanel3Layout.createParallelGroup()
																									.addGroup(GroupLayout.Alignment.LEADING, jPanel3Layout.createSequentialGroup()
																											.addComponent(jLabel7, GroupLayout.PREFERRED_SIZE, 84, GroupLayout.PREFERRED_SIZE)
																											.addGap(84))
																											.addGroup(jPanel3Layout.createSequentialGroup()
																													.addPreferredGap(jLabel7, jLabel4, LayoutStyle.ComponentPlacement.INDENT)
																													.addGroup(jPanel3Layout.createParallelGroup()
																															.addGroup(GroupLayout.Alignment.LEADING, jPanel3Layout.createSequentialGroup()
																																	.addComponent(jLabel4, GroupLayout.PREFERRED_SIZE, 134, GroupLayout.PREFERRED_SIZE)
																																	.addGap(22))
																																	.addGroup(GroupLayout.Alignment.LEADING, jPanel3Layout.createSequentialGroup()
																																			.addComponent(jLabel5, GroupLayout.PREFERRED_SIZE, 148, GroupLayout.PREFERRED_SIZE)
																																			.addGap(8))
																																			.addComponent(jLabel3, GroupLayout.Alignment.LEADING, GroupLayout.PREFERRED_SIZE, 156, GroupLayout.PREFERRED_SIZE))))
																																			.addGap(30)
																																			.addGroup(jPanel3Layout.createParallelGroup()
																																					.addGroup(jPanel3Layout.createSequentialGroup()
																																							.addComponent(jTextField3, GroupLayout.PREFERRED_SIZE, 41, GroupLayout.PREFERRED_SIZE))
																																							.addGroup(jPanel3Layout.createSequentialGroup()
																																									.addComponent(jTextField1, GroupLayout.PREFERRED_SIZE, 41, GroupLayout.PREFERRED_SIZE))
																																									.addGroup(jPanel3Layout.createSequentialGroup()
																																											.addComponent(jTextField2, GroupLayout.PREFERRED_SIZE, 41, GroupLayout.PREFERRED_SIZE)))
																																											.addContainerGap(109, Short.MAX_VALUE));
							jPanel3Layout.setVerticalGroup(jPanel3Layout.createParallelGroup()
									.addComponent(jSeparator1, GroupLayout.Alignment.LEADING, 0, 123, Short.MAX_VALUE)
									.addGroup(jPanel3Layout.createSequentialGroup()
											.addGap(12)
											.addGroup(jPanel3Layout.createParallelGroup(GroupLayout.Alignment.BASELINE)
													.addComponent(jLabel7, GroupLayout.Alignment.BASELINE, GroupLayout.PREFERRED_SIZE, GroupLayout.PREFERRED_SIZE, GroupLayout.PREFERRED_SIZE)
													.addComponent(jLabel6, GroupLayout.Alignment.BASELINE, GroupLayout.PREFERRED_SIZE, GroupLayout.PREFERRED_SIZE, GroupLayout.PREFERRED_SIZE))
													.addGap(11)
													.addGroup(jPanel3Layout.createParallelGroup(GroupLayout.Alignment.BASELINE)
															.addComponent(jComboBox1, GroupLayout.Alignment.BASELINE, GroupLayout.PREFERRED_SIZE, GroupLayout.PREFERRED_SIZE, GroupLayout.PREFERRED_SIZE)
															.addComponent(jTextField1, GroupLayout.Alignment.BASELINE, GroupLayout.PREFERRED_SIZE, GroupLayout.PREFERRED_SIZE, GroupLayout.PREFERRED_SIZE)
															.addComponent(jLabel3, GroupLayout.Alignment.BASELINE, GroupLayout.PREFERRED_SIZE, GroupLayout.PREFERRED_SIZE, GroupLayout.PREFERRED_SIZE)
															.addComponent(jLabel1, GroupLayout.Alignment.BASELINE, GroupLayout.PREFERRED_SIZE, GroupLayout.PREFERRED_SIZE, GroupLayout.PREFERRED_SIZE))
															.addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
															.addGroup(jPanel3Layout.createParallelGroup(GroupLayout.Alignment.BASELINE)
																	.addComponent(jTextField2, GroupLayout.Alignment.BASELINE, GroupLayout.PREFERRED_SIZE, GroupLayout.PREFERRED_SIZE, GroupLayout.PREFERRED_SIZE)
																	.addComponent(jLabel5, GroupLayout.Alignment.BASELINE, GroupLayout.PREFERRED_SIZE, GroupLayout.PREFERRED_SIZE, GroupLayout.PREFERRED_SIZE)
																	.addComponent(jTextField4, GroupLayout.Alignment.BASELINE, GroupLayout.PREFERRED_SIZE, GroupLayout.PREFERRED_SIZE, GroupLayout.PREFERRED_SIZE)
																	.addComponent(jLabel2, GroupLayout.Alignment.BASELINE, GroupLayout.PREFERRED_SIZE, GroupLayout.PREFERRED_SIZE, GroupLayout.PREFERRED_SIZE))
																	.addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
																	.addGroup(jPanel3Layout.createParallelGroup(GroupLayout.Alignment.BASELINE)
																			.addComponent(jTextField3, GroupLayout.Alignment.BASELINE, GroupLayout.PREFERRED_SIZE, GroupLayout.PREFERRED_SIZE, GroupLayout.PREFERRED_SIZE)
																			.addComponent(jLabel4, GroupLayout.Alignment.BASELINE, GroupLayout.PREFERRED_SIZE, GroupLayout.PREFERRED_SIZE, GroupLayout.PREFERRED_SIZE))
																			.addGap(6, 6, 6)));
						}
						{
							jPanel2 = new JPanel();
							FlowLayout jPanel2Layout = new FlowLayout();
							jPanel2.setLayout(jPanel2Layout);
							jPanel2.setBorder(BorderFactory.createEtchedBorder(BevelBorder.LOWERED));
							{
								jScrollPane1 = new JScrollPane();
								jPanel2.add(jScrollPane1);
								jScrollPane1.setPreferredSize(new java.awt.Dimension(180, 189));
								jScrollPane1.getHorizontalScrollBar().setEnabled(true);
								jScrollPane1.getHorizontalScrollBar().setOpaque(true);
								jScrollPane1.setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_NEVER);
								{
									jTextArea1 = new JTextArea();
									jScrollPane1.setViewportView(jTextArea1);
									jTextArea1.setEditable(false);
									jTextArea1.setPreferredSize(new java.awt.Dimension(180, 189));
								}
							}
						}
						jPanel1Layout1.setHorizontalGroup(jPanel1Layout1.createSequentialGroup()
							.addGap(6)
							.addComponent(jPanel4, GroupLayout.PREFERRED_SIZE, 190, GroupLayout.PREFERRED_SIZE)
							.addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
							.addGroup(jPanel1Layout1.createParallelGroup()
							    .addGroup(jPanel1Layout1.createSequentialGroup()
							        .addComponent(jPanel3, GroupLayout.PREFERRED_SIZE, 547, GroupLayout.PREFERRED_SIZE)
							        .addGap(0, 0, Short.MAX_VALUE))
							    .addGroup(GroupLayout.Alignment.LEADING, jPanel1Layout1.createSequentialGroup()
							        .addComponent(jPanel2, 0, 189, Short.MAX_VALUE)
							        .addGap(358)))
							.addPreferredGap(LayoutStyle.ComponentPlacement.RELATED));
						jPanel1Layout1.setVerticalGroup(jPanel1Layout1.createSequentialGroup()
							.addGap(8)
							.addGroup(jPanel1Layout1.createParallelGroup()
							    .addGroup(GroupLayout.Alignment.LEADING, jPanel1Layout1.createSequentialGroup()
							        .addComponent(jPanel3, GroupLayout.PREFERRED_SIZE, 130, GroupLayout.PREFERRED_SIZE)
							        .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
							        .addComponent(jPanel2, GroupLayout.PREFERRED_SIZE, 202, GroupLayout.PREFERRED_SIZE)
							        .addGap(0, 201, Short.MAX_VALUE))
							    .addGroup(jPanel1Layout1.createSequentialGroup()
							        .addComponent(jPanel4, GroupLayout.PREFERRED_SIZE, 539, GroupLayout.PREFERRED_SIZE)
							        .addGap(0, 0, Short.MAX_VALUE)))
							.addPreferredGap(LayoutStyle.ComponentPlacement.RELATED));
			}
			this.setSize(762, 604);
			{
				jMenuBar1 = new JMenuBar();
				setJMenuBar(jMenuBar1);
				{
					jMenu3 = new JMenu();
					jMenuBar1.add(jMenu3);
					jMenu3.setText("File");
					{
						newFileMenuItem = new JMenuItem();
						jMenu3.add(newFileMenuItem);
						newFileMenuItem.setText("New");
					}
					{
						openFileMenuItem = new JMenuItem();
						jMenu3.add(openFileMenuItem);
						openFileMenuItem.setText("Open");
					}
					{
						saveMenuItem = new JMenuItem();
						jMenu3.add(saveMenuItem);
						saveMenuItem.setText("Save");
					}
					{
						saveAsMenuItem = new JMenuItem();
						jMenu3.add(saveAsMenuItem);
						saveAsMenuItem.setText("Save As ...");
					}
					{
						closeFileMenuItem = new JMenuItem();
						jMenu3.add(closeFileMenuItem);
						closeFileMenuItem.setText("Close");
					}
					{
						jSeparator2 = new JSeparator();
						jMenu3.add(jSeparator2);
					}
					{
						exitMenuItem = new JMenuItem();
						jMenu3.add(exitMenuItem);
						exitMenuItem.setText("Exit");
					}
				}
				{
					jMenu5 = new JMenu();
					jMenuBar1.add(jMenu5);
					jMenu5.setText("Help");
					{
						helpMenuItem = new JMenuItem();
						jMenu5.add(helpMenuItem);
						helpMenuItem.setText("Help");
					}
				}
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

}
