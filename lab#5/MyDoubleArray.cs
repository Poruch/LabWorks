
using DataManage;
using System;

namespace MyTypes
{
    class MyDoubleArray : Collection<double>
    {
        private static Random rand = new Random();
        private int start = 0;
        private int end = 10;
        public void SetBorderRand(int start, int end)
        {
            this.start = start;
            this.end = end;
        }

        public double Sum
        {
            get
            {
                double sum = 0;
                for (int i = 0; i < Count; i++)
                {
                    sum += items[i];
                }
                return sum;
            }
        }
        public double Average
        {
            get
            {
                return (double)Sum / Count;
            }
        }
        public bool isEmpty
        {
            get
            {
                return Count == 0 || items == null;
            }
        }
        public double Max
        {
            get
            {
                if (isEmpty)
                {
                    Console.WriteLine("В массиве нет максимума массив пуст");
                    return -1;
                }
                double max = double.MinValue;
                for (int i = 0; i < Count; i++)
                    max = max > items[i] ? max : items[i];
                return max;
            }
        }
        public double Min
        {
            get
            {
                if (isEmpty)
                {
                    Console.WriteLine("В массиве нет минимума массив пуст");
                    return -1;
                }
                double max = double.MaxValue;
                for (int i = 0; i < Count; i++)
                    max = max < items[i] ? max : items[i];
                return max;
            }
        }

        public MyDoubleArray(int size, bool fill = false) : base(size)
        {
            if (fill) Fill();
        }
        public MyDoubleArray(double[] numbers) : base(numbers)
        {

        }
        /// <summary>
        /// if random is true then array will fill random numbers
        /// else elements of array will be entered from console
        /// </summary>
        /// <param name="mode"></param>
        public void Fill(bool random = true)
        {
            if (random)
            {
                for (int i = 0; i < Count; i++)
                    items[i] = rand.NextDouble() * (end - start) + start;
            }
            else
            {
                for (int i = 0; i < Count; i++)
                    items[i] = InputManager.ReadValueDouble();
            }
        }




        public void AddElem(int ind, int count = 1, bool fill = false, bool random = true)
        {
            if (!(ind <= Count && ind >= 0))
            {
                Console.WriteLine("Ошибка в количестве добавляемых элементов");
                return;
            }
            int newLen = items.Length;
            while (Count + count > newLen)
                newLen *= 2;
            SetSize(newLen);
            for (int i = ind; i < Count; i++)
            {
                items[i + count] = items[i];
            }
            if (fill)
                for (int i = ind; i <= ind + count - 1; i++)
                {
                    if (random)
                        items[i] = rand.NextDouble() * (end - start) + start;
                    else
                        items[i] = InputManager.ReadValueDouble();
                }
            Count += count;
        }


        public void SortInsets(bool rise = true)
        {
            for (int i = 0; i < Count; i++)
            {
                double buff = items[i];
                int j = i - 1;
                while (j >= 0 && buff < items[j])
                {
                    items[j + 1] = items[j];
                    j--;
                }
                items[j + 1] = buff;
            }
        }

        public void SelectionSort(bool rise = true)
        {
            for (int i = 0; i < Count - 1; i++)
            {
                double buff1 = items[i];
                double buff2 = !rise ? double.MinValue : double.MaxValue;
                int k = i + 1;
                for (int j = i + 1; j < Count; j++)
                {
                    if (buff2 > items[j] == rise)
                    {
                        buff2 = items[j];
                        k = j;
                    }
                }
                if (buff1 > buff2)
                {
                    items[i] = buff2;
                    items[k] = buff1;
                }
            }

        }
        public void BubbleSort(bool rise = true)
        {
            for (int i = 0; i < Count - 1; i++)
            {
                for (int j = i + 1; j < Count; j++)
                {
                    double buff = items[j];
                    if (items[i] > items[j] == rise)
                    {
                        items[j] = items[i];
                        items[i] = buff;
                    }
                }
            }
        }
        /// <summary>
        /// 
        /// </summary>
        /// <param name="value"></param>
        /// <returns></returns>
        public int GetIndex(double value)
        {
            for (int i = 0; i < Count; i++)
            {
                if (items[i] == value)
                    return i;
            }
            Console.WriteLine("Такого элемента нет, индекс вернуть невозможно");
            return -1;
        }

        /// <summary>
        /// For binary search, your array should be sorted
        /// </summary>
        /// <param name="number"></param>
        /// <returns></returns>
        public int GetIndexBinary(double value)
        {
            int offsetLeft = 0;
            int offsetRight = Count / 2;
            while (offsetRight != 0)
            {
                if (items[offsetLeft + offsetRight] == value)
                    return offsetLeft + offsetRight;
                else if (items[offsetLeft + offsetRight] > value)
                {
                    offsetRight /= 2;
                }
                else if (items[offsetLeft + offsetRight] < value)
                {
                    offsetLeft += offsetRight;
                    offsetRight /= 2;
                }
            }
            Console.WriteLine("Такого элемента нет, индекс вернуть невозможно");
            return -1;
        }

        public bool Contains(double value)
        {
            for (int i = 0; i < Count; i++)
            {
                if (items[i] == value)
                    return true;
            }
            return false;
        }

        /// <summary>
        /// For binary search, your array should be sorted
        /// </summary>
        /// <param name="number"></param>
        /// <returns></returns>
        public bool ContainsBinary(double value)
        {
            int offsetLeft = 0;
            int offsetRight = Count / 2;
            while (offsetRight != 0)
            {
                if (items[offsetLeft + offsetRight] == value)
                    return true;
                else if (items[offsetLeft + offsetRight] > value)
                {
                    offsetRight /= 2;
                }
                else if (items[offsetLeft + offsetRight] < value)
                {
                    offsetLeft += offsetRight;
                    offsetRight /= 2;
                }
            }
            return false;
        }
        public void Write(int count)
        {
            for (int i = 0; i < Count; i++)
            {
                if (i % 10 != 0)
                    Console.ForegroundColor = (ConsoleColor)(i % 10);
                Console.Write(items[i].ToString().Substring(0,count) + " ");
            }
            Console.WriteLine();
            Console.ForegroundColor = ConsoleColor.White;
        }

    }
}
