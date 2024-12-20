using System;
namespace MyTypes
{
    internal class MyTornMatrix : MyCollection<MyIntArray>
    {

        public MyTornMatrix(int rows, int columns, bool autoFill = false) : base(rows)
        {
            for (int i = 0; i < rows; i++)
            {
                items[i] = new MyIntArray(columns);
                if (autoFill) items[i].Fill();
            }

        }
        public MyTornMatrix(int rows, int[] columns, bool autoFill = false) : base(rows)
        {
            if (rows == columns.Length)
                for (int i = 0; i < rows; i++)
                {
                    items[i] = new MyIntArray(columns[i]);
                    if (autoFill) items[i].Fill();
                }
            else
            {
                throw new ArgumentException("Количество строк не равно количеству столбцов");
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
            for (int i = 0; i < Count; i++)
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
