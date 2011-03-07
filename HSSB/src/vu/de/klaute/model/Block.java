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

import java.util.ArrayList;

/**
 * @author klaute
 *
 */
public class Block
{
	
	private static int maxTuples = -1;
	
	private ArrayList<Tupel> tuples = new ArrayList<Tupel>();
	
	/**
	 * 
	 * @param i
	 */
	public Block(int i)
	{
		if ( Block.maxTuples == -1 )
		{
			Block.maxTuples = i;
			for (int j = 0; j < Block.maxTuples; j++)
			{
				this.tuples.add(new Tupel(j,0));
			}
		}
	}

	/**
	 * 
	 */
	public Block() {

	}

	/**
	 * 
	 * @param t
	 * @return
	 */
	public boolean addTupel(Tupel t)
	{
		if ( t == null )
		{
			return false;
		}
		for (Tupel tmp : tuples)
		{
			if ( tmp.getIndex() == t.getIndex() )
			{
				tmp.setValue(t.getValue());
				return true;
			}
		}
		if ( tuples.size() >= Block.maxTuples && Block.maxTuples != -1 )
		{
			return false;
		}
		return tuples.add(t);
	}
	
	/**
	 * 
	 * @param t
	 * @return
	 */
	public boolean removeTupel(Tupel t)
	{
		if (t== null)
		{
			return false;
		}
		return tuples.remove(t);
	}
	
	/**
	 * 
	 * @return
	 */
	@Override
	public String toString()
	{
		String tmp = String.format( "0x%02x\n", this.tuples.size() );
		
		if ( Block.maxTuples == -1 )
		{
			Block.maxTuples = this.tuples.size();
		}
		
		for (Tupel t : tuples)
		{
			tmp += t;
		}
		return tmp;
	}
	
	/**
	 * 
	 * @param args
	 */
	public static void main(String args[])
	{
		Block b = new Block(8);
		b.addTupel(new Tupel(0,1));    // KeyReport-Data
		b.addTupel(new Tupel(2,0x53)); // Press "Num Lock"-Key
		
		System.out.println("block:\n"+b);
		
	}
	
}
