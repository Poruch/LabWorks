using System;
using System.Collections;

namespace MyTypes
{
    delegate T Criterion<T,J>(J a);
    class MyArray : IEnumerable, IEnumerator
    {
        private int[] ints;
        private int length;


        private Random rand = new Random();
        private int start = 0;
        private int end = 10;
        private bool isRiseSorted
        {
            get
            {
                for (int i = 0; i < length - 1; i++)
                {
                    if (ints[i] > ints[i + 1])
                        return false;
                }
                return true;
            }
        }
        private bool isFallSorted
        {
            get
            {
                for (int i = 0; i < length - 1; i++)
                {
                    if (ints[i] < ints[i + 1])
                        return false;
                }
                return true;
            }
        }
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
                    Console.WriteLine("� ������� ��� ��������� ������ ����");
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
                    Console.WriteLine("� ������� ��� �������� ������ ����");
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
                    ints[i] = GeneralFunc.ReadValueInt();
            }
        }
        public void DeleteElem(int ind)
        {
            if (!inBorder(ind))
            {
                Console.WriteLine("�������� �������� ���������� ������� ���������� ��� ������ �������");
                return;
            }
            var currarray = new int[ints.Length];
            int j = 0;
            for (int i = 0; i < ind; i++)
            {
                currarray[j++] = ints[i];
            }
            for (int i = ind + 1; i < length; i++)
            {
                currarray[j++] = ints[i];
            }
            Console.WriteLine("������ ������� - " + ints[ind].ToString());
            length--;
            Ints = currarray;
        }
        public void DeleteElem(Criterion<bool,int> criterion)
        {
            var currarray = new int[length];
            int[] result;
            int count = 0;
            Console.Write("������� �������� - ");
            for (int i = 0; i < length; i++)
            {
                if (!criterion(ints[i]))
                    currarray[count++] = ints[i];
                else
                    Console.Write(ints[i].ToString() + " ");
            }
            Console.WriteLine();
            result = new int[ints.Length];
            for (int i = 0; i < count; i++)
            {
                result[i] = currarray[i];
            }
            length = count;
            Ints = result;
        }

        public void Insert(int ind, MyArray array)
        {
            if (!(ind <= length && ind >= 0))
            {
                Console.WriteLine("������ � ���������� ����������� ���������");
                return;
            }

            int[] result;
            int newLen = ints.Length;
            while (length + array.Count > newLen)
                newLen *= 2;
            result = new int[newLen];

            for (int i = 0; i < ind; i++)
            {
                result[i] = ints[i];
            }

            for (int i = ind; i < array.Count; i++)
                result[i] = array[i - ind];

            for (int i = ind + array.Count; i < Count + array.Count; i++)
                result[i] = ints[i - array.Count];

            length += array.Count;
            Ints = result;
        }

        public void AddElem(int ind, int value)
        {
            if (!(ind <= length && ind >= 0))
            {
                Console.WriteLine("������ � ���������� ����������� ���������");
                return;
            }
            int[] result;
            int newLen = ints.Length;
            while (Count + 1 > newLen)
                newLen *= 2;
            result = new int[newLen];

            for (int i = 0; i < ind; i++)
            {
                result[i] = ints[i];
            }
            for (int i = ind; i < Count; i++)
            {
                result[i + 1] = ints[i];
            }
            result[ind] = value;

            length++;
            Ints = result;
        }    
        public void AddElem(int ind, int count = 1, bool fill = false, bool random = true)
        {
            if (! (ind <= length && ind >= 0))
            {
                Console.WriteLine("������ � ���������� ����������� ���������");
                return;
            }
            int[] result;
            int newLen = ints.Length;
            while (Count + count > newLen)
                newLen *= 2;
            result = new int[newLen];

            for (int i = 0; i < ind; i++)
            {
                result[i] = ints[i];
            }
            for (int i = ind; i < length; i++)
            {
                result[i + count] = ints[i];
            }
            if (fill)
                for (int i = ind; i <= ind + count - 1; i++)
                {
                    if (random)
                        result[i] = rand.Next(start, end);
                    else
                        result[i] = GeneralFunc.ReadValueInt();
                }
            length += count;
            Ints = result;
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
            count = count % Count;
            int[] result = new int[ints.Length];
            int k = 0;
            if (right)
            {
                for (int i = length - count; i < length; i++)
                    result[k++] = ints[i];
                for (int i = 0; i < Count - count; i++)
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

        public int FindFirst(Criterion<bool,int> criterion)
        {
            for (int i = 0; i < length; i++)
            {
                if (criterion(ints[i]))
                {
                    return ints[i];
                }
            }
            Console.WriteLine("�� ���� ������� �� ������� �� ��������");
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
            Console.WriteLine("�� ���� ������� �� ������� �� ��������");
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
                for (int j = i - 1; j >= 0; j--)
                {
                    if (buff < ints[j] == rise)
                    {
                        ints[j + 1] = ints[j];
                        ints[j] = buff;
                    }
                    else
                        break;
                }
            }
        }

        public void SelectionSort(bool rise = true)
        {
            for (int i = 0; i < length - 2; i++)
            {
                int buff1 = ints[i];
                int buff2 = ints[i + 1];
                int k = i + 1;
                for (int j = i + 2; j < length; j++)
                {
                    if (buff2 > ints[j] == rise)
                    {
                        buff2 = ints[j];
                        k = j;
                    }
                }
                ints[i] = buff2;
                ints[k] = buff1;
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
            Console.WriteLine("������ �������� ���, ������ ������� ����������");
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
            Console.WriteLine("������ �������� ���, ������ ������� ����������");
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
                Console.Write(ints[i].ToString() + " ");
            }
            Console.WriteLine();
        }

        public bool inBorder(int ind)
        {
            return ind < length && ind >= 0;
        }

        public int this[int key]
        {
            get
            {
                if (!inBorder(key))
                {
                    Console.WriteLine("����� �� ������� �������");
                    return 0;
                }
                return ints[key];
            }
            set
            {
                if (!inBorder(key))
                {
                    Console.WriteLine("����� �� ������� �������");
                    return;
                }
                ints[key] = value;
            }
        }
        public MyArray Copy(int indS)
        {
            if (!inBorder(indS))
            {
                Console.WriteLine("����� �� ������� �������");
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
                Console.WriteLine("����� �� ������� �������");
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
                    Console.WriteLine("������� �������� ���������");
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