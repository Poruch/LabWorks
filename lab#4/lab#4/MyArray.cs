using lab_4;
using System;
using System.Collections;

namespace MyTypes
{
    delegate T Criterion<T, J>(J a);
    class MyArray : IEnumerable, IEnumerator
    {
        private int[] ints;
        private int length;

        private Random rand = new Random();
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
                for (int i = 0; i < length; i++)
                {
                    sum += ints[i];
                }
                return sum;
            }
        }
        public double Average
        {
            get
            {
                return (double)Sum / length;
            }
        }
        public bool isEmpty
        {
            get
            {
                return length == 0 || ints == null;
            }
        }
        public int Count
        {
            get { return length; }
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
                for (int i = 0; i < length; i++)
                    max = max > ints[i] ? max : ints[i];
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
                for (int i = 0; i < length; i++)
                    max = max < ints[i] ? max : ints[i];
                return max;
            }
        }
        private int[] Ints
        {
            set
            {
                ints = value;
                //WriteArray();
            }
        }
        public MyArray(int size)
        {
            int p = 2;
            while (p < size) p *= 2;
            ints = new int[p];
            length = size;
        }
        public MyArray(int[] numbers)
        {
            int p = 2;
            while (p < numbers.Length) p *= 2;
            ints = new int[p];
            for (int i = 0; i < numbers.Length; i++)
                ints[i] = numbers[i];
            length = numbers.Length;
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
                for (int i = 0; i < length; i++)
                    ints[i] = rand.Next(start, end);
            }
            else
            {
                for (int i = 0; i < length; i++)
                    ints[i] = Program.ReadValueInt();
            }
        }
        public void DeleteElem(int ind)
        {
            if (!inBorder(ind))
            {
                Console.WriteLine("Удаление элемента невозможно элемент находиться вне границ массива");
                return;
            }
            int j = 0;
            Console.WriteLine("Удален элемент - " + ints[ind].ToString());
            for (int i = 0; i < ind; i++)
            {
                ints[j++] = ints[i];
            }
            for (int i = ind + 1; i < length; i++)
            {
                ints[j++] = ints[i];
            }
            length--;
            int newLen = 1;
            while (newLen <= length)
                newLen *= 2;
            SetSize(newLen);
        }
        public void DeleteElem(Criterion<bool, int> criterion)
        {
            var currarray = new int[length];
            int count = 0;
            Console.Write("Удалены элементы - ");
            for (int i = 0; i < length; i++)
            {
                if (!criterion(ints[i]))
                    currarray[count++] = ints[i];
                else
                    Console.Write(ints[i].ToString() + " ");
            }
            Console.WriteLine();
            for (int i = 0; i < count; i++)
            {
                ints[i] = currarray[i];
            }
            int newLen = 1;
            while (newLen <= count)
                newLen *= 2;
            SetSize(newLen);
            length = count;
        }
        public void Insert(int ind, MyArray array)
        {
            if (!(ind <= length && ind >= 0))
            {
                Console.WriteLine("Ошибка в количестве добавляемых элементов");
                return;
            }
            int newLen = ints.Length;
            while (length + array.Count > newLen)
                newLen *= 2;
            SetSize(newLen);

            for (int i = length + array.Count; i >= ind + array.Count; i--)
                ints[i] = ints[i - array.Count];
            for (int i = ind; i < array.Count; i++)
                ints[i] = array[i - ind];
            length += array.Count;
        }
        public void Insert(int ind, int[] array)
        {
            if (!(ind <= length && ind >= 0))
            {
                Console.WriteLine("Ошибка в количестве добавляемых элементов");
                return;
            }
            int newLen = ints.Length;
            while (length + array.Length > newLen)
                newLen *= 2;
            SetSize(newLen);
            for (int i = length + array.Length; i >= ind + array.Length; i--)
                ints[i] = ints[i - array.Length];
            for (int i = ind; i < array.Length; i++)
                ints[i] = array[i - ind];
            length += array.Length;
        }
        public void AddElem(int ind, int value)
        {
            if (!(ind <= length && ind >= 0))
            {
                Console.WriteLine("Ошибка в количестве добавляемых элементов");
                return;
            }
            int newLen = ints.Length;
            while (length + 1 > newLen)
                newLen *= 2;
            SetSize(newLen);

            for (int i = ind; i < length; i++)
            {
                ints[i + 1] = ints[i];
            }
            ints[ind] = value;
            length++;
        }
        public void AddElem(int ind, int count = 1, bool fill = false, bool random = true)
        {
            if (!(ind <= length && ind >= 0))
            {
                Console.WriteLine("Ошибка в количестве добавляемых элементов");
                return;
            }
            int newLen = ints.Length;
            while (length + count > newLen)
                newLen *= 2;
            SetSize(newLen);
            for (int i = ind; i < length; i++)
            {
                ints[i + count] = ints[i];
            }
            if (fill)
                for (int i = ind; i <= ind + count - 1; i++)
                {
                    if (random)
                        ints[i] = rand.Next(start, end);
                    else
                        ints[i] = Program.ReadValueInt();
                }
            length += count;
        }

        public void Reverse()
        {
            int[] result = new int[ints.Length];
            int j = length - 1;
            for (int i = 0; i < length; i++)
                result[i] = ints[j--];
            Ints = result;
        }

        public void Move(int count, bool right = true)
        {
            if (length == 0)
                return;
            count = count % length;
            int[] result = new int[ints.Length];
            int k = 0;
            if (right)
            {
                for (int i = length - count; i < length; i++)
                    result[k++] = ints[i];
                for (int i = 0; i < length - count; i++)
                    result[k++] = ints[i];
            }
            else
            {
                for (int i = count; i < length; i++)
                    result[k++] = ints[i];
                for (int i = 0; i < count; i++)
                    result[k++] = ints[i];
            }
            ints = result;
        }

        public int FindFirst(Criterion<bool, int> criterion)
        {
            for (int i = 0; i < length; i++)
            {
                if (criterion(ints[i]))
                {
                    return ints[i];
                }
            }
            Console.WriteLine("Ни один элемент не подешел по критерию");
            return -1;
        }
        public int FindLast(Func<int, bool> criterion)
        {
            for (int i = length; i >= 0; i--)
            {
                if (criterion(ints[i]))
                {
                    return ints[i];
                }
            }
            Console.WriteLine("Ни один элемент не подешел по критерию");
            return -1;
        }
        public MyArray FindAll(Criterion<bool, int> criterion)
        {
            var currarray = new int[length];
            int[] result;
            int k = 0;
            for (int i = 0; i < length; i++)
                if (criterion(ints[i]))
                    currarray[k++] = ints[i];

            result = new int[k];
            for (int i = 0; i < k; i++)
            {
                result[i] = currarray[i];
            }

            return new MyArray(result);
        }

        public void SortInsets(bool rise = true)
        {
            for (int i = 0; i < length; i++)
            {
                int buff = ints[i];
                int j = i - 1;
                while (j >= 0 && (buff < ints[j] == rise))
                {
                    ints[j + 1] = ints[j];
                    j--;
                }
                ints[j + 1] = buff;
            }
        }

        public void SelectionSort(bool rise = true)
        {
            for (int i = 0; i < length - 1; i++)
            {
                int buff1 = ints[i];
                int buff2 = !rise ? int.MinValue : int.MaxValue;
                int k = i + 1;
                for (int j = i + 1; j < length; j++)
                {
                    if (buff2 > ints[j] == rise)
                    {
                        buff2 = ints[j];
                        k = j;
                    }
                }
                if (buff1 > buff2 == rise)
                {
                    ints[i] = buff2;
                    ints[k] = buff1;
                }
            }

        }

        public void BubbleSort(bool rise = true)
        {
            for (int i = 0; i < length - 1; i++)
            {
                for (int j = i + 1; j < length; j++)
                {
                    int buff = ints[j];
                    if (ints[i] > ints[j] == rise)
                    {
                        ints[j] = ints[i];
                        ints[i] = buff;
                    }
                }
            }
        }
        public void Clear()
        {
            for (int i = 0; i < length; i++)
                ints[i] = 0;
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="value"></param>
        /// <returns></returns>
        public int GetIndex(int value)
        {
            for (int i = 0; i < length; i++)
            {
                if (ints[i] == value)
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
            int offsetRight = length / 2;
            while (offsetRight != 0)
            {
                if (ints[offsetLeft + offsetRight] == value)
                    return offsetLeft + offsetRight;
                else if (ints[offsetLeft + offsetRight] > value)
                {
                    offsetRight /= 2;
                }
                else if (ints[offsetLeft + offsetRight] < value)
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
            for (int i = 0; i < length; i++)
            {
                if (ints[i] == value)
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
            int offsetRight = length / 2;
            while (offsetRight != 0)
            {
                if (ints[offsetLeft + offsetRight] == value)
                    return true;
                else if (ints[offsetLeft + offsetRight] > value)
                {
                    offsetRight /= 2;
                }
                else if (ints[offsetLeft + offsetRight] < value)
                {
                    offsetLeft += offsetRight;
                    offsetRight /= 2;
                }
            }
            return false;
        }
        public void WriteArray()
        {
            for (int i = 0; i < length; i++)
            {
                if (i % 10 != 0)
                    Console.ForegroundColor = (ConsoleColor)(i % 10);
                Console.Write(ints[i].ToString() + " ");
            }
            Console.WriteLine();
            Console.ForegroundColor = ConsoleColor.White;
        }

        public bool inBorder(int ind)
        {
            return ind < length && ind >= 0;
        }

        private void SetSize(int size)
        {
            if (size == ints.Length) return;
            var result = new int[size];
            for (int i = 0; i < (length > size ? size : length); i++)
                result[i] = ints[i];
            ints = result;
        }
        public int this[int key]
        {
            get
            {
                if (!inBorder(key))
                {
                    Console.WriteLine("Выход за границы массива");
                    return 0;
                }
                return ints[key];
            }
            set
            {
                if (!inBorder(key))
                {
                    Console.WriteLine("Выход за границы массива");
                    return;
                }
                ints[key] = value;
            }
        }
        public MyArray Copy(int indS)
        {
            if (!inBorder(indS))
            {
                Console.WriteLine("Выход за границы массива");
                return new MyArray(0);
            }
            MyArray result = new MyArray(Count - indS);
            for (int i = indS; i < Count; i++)
                result[i - indS] = ints[i];
            return result;
        }
        public MyArray Copy(int indS, int indE)
        {
            if (!inBorder(indS) || !inBorder(indE))
            {
                Console.WriteLine("Выход за границы массива");
                return new MyArray(0);
            }
            MyArray result = new MyArray(indE - indS);
            for (int i = indS; i < indE; i++)
                result[i - indS] = ints[i];
            return result;
        }

        public static MyArray operator +(MyArray arr1, MyArray arr2)
        {
            MyArray result = new MyArray(arr1.Count + arr2.Count);
            int count = 0;
            for (int i = 0; i < arr1.Count; i++)
                result[count++] = arr1[i];
            for (int i = 0; i < arr2.Count; i++)
                result[count++] = arr2[i];
            return result;
        }



        public IEnumerator GetEnumerator()
        {
            return this;
        }

        public object Current
        {
            get
            {
                if (!inBorder(index))
                {
                    Console.WriteLine("Сначала сдвиньте указатель");
                }
                return ints[index];
            }
        }
        int index = -1;

        public bool MoveNext()
        {
            index++;
            if (index < length && index > -1)
                return true;
            else
                return false;
        }

        public void Reset()
        {
            index = -1;
        }
    }
}