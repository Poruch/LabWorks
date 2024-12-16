using DataManage;
using System;

namespace MyTypes
{
    class MyIntArray : MyCollection<int>
    {
        private static Random rand = new Random();
        private int start = 0;
        private int end = 10;
        public void SetBorderRand(int start, int end)
        {
            this.start = start;
            this.end = end;
        }

        public int Sum
        {
            get
            {
                int sum = 0;
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
        public int Max
        {
            get
            {
                if (isEmpty)
                {
                    Console.WriteLine("В массиве нет максимума массив пуст");
                    return -1;
                }
                int max = int.MinValue;
                for (int i = 0; i < Count; i++)
                    max = max > items[i] ? max : items[i];
                return max;
            }
        }
        public int Min
        {
            get
            {
                if (isEmpty)
                {
                    Console.WriteLine("В массиве нет минимума массив пуст");
                    return -1;
                }
                int max = int.MaxValue;
                for (int i = 0; i < Count; i++)
                    max = max < items[i] ? max : items[i];
                return max;
            }
        }
        public MyIntArray(int size) : base(size)
        {
            int p = 2;
            while (p < size) p *= 2;
            items = new int[p];
            Count = size;
        }
        public MyIntArray(int[] numbers) : base(numbers.Length)
        {
            int p = 2;
            while (p < numbers.Length) p *= 2;
            items = new int[p];
            for (int i = 0; i < numbers.Length; i++)
                items[i] = numbers[i];
            Count = numbers.Length;
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
                    items[i] = rand.Next(start, end);
            }
            else
            {
                for (int i = 0; i < Count; i++)
                    items[i] = InputManager.ReadValueInt();
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
                        items[i] = rand.Next(start, end);
                    else
                        items[i] = InputManager.ReadValueInt();
                }
            Count += count;
        }



        public void SortInsets(bool rise = true)
        {
            for (int i = 0; i < Count; i++)
            {
                int buff = items[i];
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
            for (int i = 0; i < Count    - 1; i++)
            {
                int buff1 = items[i];
                int buff2 = !rise ? int.MinValue : int.MaxValue;
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
                    int buff = items[j];
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
        public int GetIndex(int value)
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
        public int GetIndexBinary(int value)
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

        public bool Contains(int value)
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
        public bool ContainsBinary(int value)
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

        public void Write()
        {
            for (int i = 0; i < Count; i++)
            {
                if (i % 10 != 0)
                    Console.ForegroundColor = (ConsoleColor)(i % 10);
                Console.Write(items[i].ToString() + " ");
            }
            Console.WriteLine();
            Console.ForegroundColor = ConsoleColor.White;
        }


    }
}