using DataManage;
using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab_5
{
    internal class MyMatrix
    {
        private static Random rand = new Random();
        int[,] numbers;
        public int Row;
        public int Column;
        public MyMatrix(int row,int column)
        {
            numbers = new int[row, column];
            Row = row; 
            Column = column;
        }
        public void Fill(bool random)
        {
            if(random) 
                for (int i = 0; i < Row; i++)                
                    for(int j = 0; j < Column; j++)                    
                        numbers[i, j] = rand.Next(0, 10);
            else
                for (int i = 0; i < Row; i++)                
                    for (int j = 0; j < Column; j++)                    
                        numbers[i, j] = InputManager.ReadValueInt();     
        }
        public void Write()
        {
            for (int i = 0;i < Row; i++)
            {
                for(int j = 0;j < Column; j++)
                {
                    Console.Write(numbers[i,j] + " ");
                }
                Console.WriteLine();
            }
        }
        public void AddRows(MyMatrix matrix)
        {
            int[,] result = new int[Row + matrix.Row, Column];
            for (int i = 0; i < matrix.Row; i++)
            {
                for (int j = 0; j < Column; j++)
                {
                    result[i,j] = matrix[i,j]; 
                }
            }
            for (int i = matrix.Row; i < Row + matrix.Row; i++)
            {
                for (int j = 0; j < Column; j++)
                {
                    result[i, j] = numbers[i - matrix.Row, j];
                }
            }
            Row += matrix.Row;
            numbers = result;
        }
        public int this[int key1, int key2]
        {
            get
            {
                return numbers[key1,key2];
            }
            set
            {
                numbers[key1,key2] = value;
            }
        }
    }
}
