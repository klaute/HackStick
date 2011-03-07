/* (C) Copyright 2011 Kai Lauterbach klaute at web dot de
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

package vu.de.klaute.model;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;

/**
 * @author klaute
 *
 */
public class Sequence
{

	public static final int MAX_BLOCKS = 255;
	
	private ArrayList<Block> blocks = new ArrayList<Block>();
	private int usbDataReportSize;
	private int delayStart;
	private int delay;
	
	/**
	 * 
	 * @param s
	 * @param ds
	 * @param d
	 */
	public Sequence(int s, int ds, int d)
	{
		this.usbDataReportSize = s;
		this.delayStart = ds;
		this.delay = d;
	}
	
	public Sequence()
	{
	}

	/**
	 * 
	 * @param b
	 * @return
	 */
	public boolean addBlock(Block b)
	{
		if ( b == null )
			return false;
		return this.blocks.add(b);
	}
	
	/**
	 * 
	 * @param b
	 * @return
	 */
	public boolean removeBlock(Block b)
	{
		return this.blocks.remove(b);
	}
	
	/**
	 * 
	 * @return
	 */
	@Override
	public String toString()
	{
		String tmp = "";
		tmp += String.format("0x%02x\n", this.usbDataReportSize);
		tmp += String.format("0x%02x\n", this.delayStart);
		tmp += String.format("0x%02x\n", this.delay);
		tmp += String.format("0x%02x\n", this.blocks.size());
		for ( Block b : blocks )
		{
			tmp += b;
		}
		return tmp;
	}
	
	/**
	 * 
	 * @param fileName
	 * @return
	 */
	public boolean saveToFile(String fileName)
	{
		try {
			BufferedWriter br = new BufferedWriter(new FileWriter(fileName));
			
			br.write(this.toString());
			
			br.close();
			
		} catch (IOException e) {
			e.printStackTrace();
		}
		
		return false;
	}
	
	/**
	 * 
	 * @param fileName
	 * @return
	 */
	public static Sequence parseFile(String fileName)
	{
		Sequence seq = null;
		
		try {
			BufferedReader br = new BufferedReader(new FileReader(fileName));
			
			String zeile = "";
			try {
				
				Block block = null;
				int s       =    0;
				int ds      =    0;
				int d       =    0;
				int b       =    0;
				int i       =    0;
				int tuples  =    0;
				int status  =    0;
				
				while ( (zeile = br.readLine()) != null )
				{
					// 0x abschneiden und Hex-Wert zu Integer parsen.
					int tmp = Integer.parseInt(zeile.substring(2),16);

					switch( status )
					{
						case 0:
							s = tmp; // Anzahl der Bytes in einem dataReport.
							status = 1;
							break;
						case 1:
							ds = tmp; // Delay vor dem Start.
							status = 2;
							break;
						case 2:
							d = tmp; // Delay in ms zwischen den Blöcken.
							seq = new Sequence(s,ds,d);
							status = 3;
							break;
						case 3:
							b = tmp; // Anzahl der Blöcke.
							status = 4; // Block einlesen
							break;
						case 4:
							tuples = tmp;
							if ( tuples > 0 && b > 0 )
							{
								block = new Block(s); // Blöcke haben die Größe s
								seq.addBlock(block);
								b--; // Anzahl der zu erzeugenden Blöcke verringern
								status = 5; // Tupel einlesen (Index)
							}
							break;
						case 5:
							i = tmp;
							status = 6; // Value des Tupel einlesen
							break;
						case 6:
							block.addTupel(new Tupel(i,tmp)); // Tupel anlegen und in Block speichern
							tuples--; // Eines erzeugt, daher von der Anzahl abziehen.
							if ( tuples > 0)
							{
								status = 5; // Weiteres Tupel einlesen
							} else {
								status = 4; // Neuen Block auslesen
							}
							break;
					}
					
				}
			} catch (NumberFormatException e) {
				e.printStackTrace();
			} catch (IOException e) {
				e.printStackTrace();
			}
			
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		}
		
		return seq;
		
	}
	
	/**
	 * 
	 * @param args
	 */
	public static void main(String args[])
	{
		Block b1 = new Block(8);
		b1.addTupel(new Tupel(0,1));    // KeyReportData
		b1.addTupel(new Tupel(2,0x53)); // Press "Num Lock"-Key
		
		Block b2 = new Block();
		
		Sequence s1 = new Sequence(8, 0xff, 0x0f);
		
		b2.addTupel(new Tupel(2,0));
		
		s1.addBlock(b1);
		s1.addBlock(b2);
		
		System.out.println("sequence:\n"+s1);
		
		Sequence s2 = Sequence.parseFile("../doc/seq/keyboard_test_with_ledstatus.seq");
		
		System.out.println("sequence:\n"+s2);
		
		//s2.saveToFile("../doc/seq/keyboard_test_with_ledstatus2.seq");
		
	}
	
}
