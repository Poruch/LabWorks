using System;
using System.Diagnostics.CodeAnalysis;
using System.Linq;
using System.Net;
namespace MyTypes
{
    internal class Matrix : Collection<MyIntArray>
    {

        public Matrix(int rows,int coluoms, bool autoFill = false) : base(rows)
        {
            for (int i = 0; i < rows; i++)
            {
                items[i] = new MyIntArray(coluoms);
                if (autoFill) items[i].Fill();
            }

        }
        public Matrix(int rows, int[] coluoms, bool autoFill = false) : base(rows)
        {
            if(rows == coluoms.Length)
            for (int i = 0; i < rows; i++)
            {
                items[i] = new MyIntArray(coluoms[i]);
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
        public void AddColuom(MyIntArray coluom,int ind = 0)
        {
            for (int i = 0; i < Count; i++) 
            {
                items[i].Add(ind,coluom[i]);
            }
        }
        public void Write(int count)
        {
            for(int i = 0; i < Count; i++)
            {

                items[i].Write();
            }
        }        
        public double this[int key1, int key2]
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
