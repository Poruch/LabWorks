using System;
using System.Data.Common;
using System.Diagnostics.CodeAnalysis;
using System.Linq;
using System.Net;
namespace MyTypes
{
    internal class TornMyMatrix : MyCollection<MyIntArray>
    {
        public TornMyMatrix(int rows,int columns, bool autoFill = false) : base(rows)
        {
            for (int i = 0; i < rows; i++)
            {
                items[i] = new MyIntArray(columns);
                if (autoFill) items[i].Fill();
            }

        }
        public TornMyMatrix(int rows, int[] columns, bool autoFill = false) : base(rows)
        {
            if(rows == columns.Length)
            for (int i = 0; i < rows; i++)
            {
                items[i] = new MyIntArray(columns[i]);
                if (autoFill) items[i].Fill();
            }
            else
            {
                Console.WriteLine("Количество колонок не равно количесиву столбцов");
            }

        }
        public void Fill(bool random = true)
        {
            for (int i = 0; i < Count; i++)
            {
                items[i].Fill(random);
            }
        }
        public void AddColuom(MyIntArray column, int ind = 0)
        {
            for (int i = 0; i < Count; i++) 
            {
                items[i].Add(ind, column[i]);
            }
        }
        public void Write(int count)
        {
            for(int i = 0; i < Count; i++)
            {

                items[i].Write();
            }
        }        
        public int this[int key1, int key2]
        {
            get
            {
                return items[key1][key2];
            }
            set
            {
                items[key1][key2] = value;
            }
        }
    }
}
