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

/**
 * 
 * @author klaute
 *
 */
public class Tupel {

	private int index = 0;
	private int value = 0;
	
	/**
	 * 
	 * @param i
	 * @param j
	 */
	public Tupel(int i, int j) {
		// TODO Auto-generated constructor stub
		this.index = i;
		this.value = j;
	}
	/**
	 * @return the index
	 */
	public int getIndex() {
		return index;
	}
	/**
	 * @param index the index to set
	 */
	public void setIndex(int index) {
		this.index = index;
	}
	/**
	 * @return the value
	 */
	public int getValue() {
		return value;
	}
	/**
	 * @param value the value to set
	 */
	public void setValue(int value) {
		this.value = value;
	}
	
	/**
	 * @return
	 */
	@Override
	public String toString()
	{
		String tmp  = String.format("0x%02x\n", index);
			   tmp += String.format("0x%02x\n", value); 
		return tmp;
	}
	
}
