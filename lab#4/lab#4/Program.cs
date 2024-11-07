using System;
using System.Collections;
using System.Security.Policy;

namespace lab_4
{
    class Array : IEnumerable, IEnumerator
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
                for(int i = 0; i < length - 1; i++)
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
                    Console.WriteLine("В массиве нет максимума массив пуст");
                    return -1;
                }
                int max = int.MinValue;
                for (int i = 0;i < length; i++) 
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
        public Array(int size)
        {
            int p = 2;
            while (p < size) p *= 2;
            ints = new int[p];
            length = size;
        }
        public Array(int[] numbers)
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
            Console.WriteLine("Удален элемент - " + ints[ind].ToString());
            length--;
            Ints = currarray;
        }
        public void DeleteElem(Func<int, bool> criterion)
        {
            var currarray = new int[length];
            int[] result;
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
            result = new int[ints.Length];
            for (int i = 0; i < count; i++)
            {
                result[i] = currarray[i];
            }
            length = count;
            Ints = result;
        }

        public void Insert(int ind, Array array)
        {
            if (!inBorder(ind))
            {
                Console.WriteLine("Ошибка в количестве добавляемых элементов");
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
            if (!inBorder(ind) || (ind > ints.Length))
            {
                Console.WriteLine("Ошибка в количестве добавляемых элементов");
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
            if (!inBorder(ind) || (ind > ints.Length))
            {
                Console.WriteLine("Ошибка в количестве добавляемых элементов");
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
                        result[i] = Program.ReadValueInt();
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

        public int FindFirst(Func<int, bool> criterion)
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
        public Array FindAll(Func<int, bool> criterion)
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

            return new Array(result);
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
            for(int i = 0;i<length;i++)
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
                else if (ints[offsetLeft+offsetRight] < value)
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
            for (int i = 0; i < length; i++)
            {
                if (ints[i] == value)
                    return true;
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

        private bool inBorder(int ind)
        {
            return ind < length && ind >= 0;
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
        public Array Copy(int indS)
        {
            if (!inBorder(indS))
            {
                Console.WriteLine("Выход за границы массива");
                return new Array(0);
            }
            Array result = new Array(Count - indS);
            for (int i = indS; i < Count; i++)
                result[i - indS] = ints[i];
            return result;
        }
        public Array Copy(int indS, int indE)
        {
            if (!inBorder(indS) || !inBorder(indE))
            {
                Console.WriteLine("Выход за границы массива");
                return new Array(0);
            }
            Array result = new Array(indE - indS);
            for (int i = indS; i < indE; i++)
                result[i - indS] = ints[i];
            return result;
        }

        public static Array operator +(Array arr1, Array arr2)
        {
            Array result = new Array(arr1.Count + arr2.Count);
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

    internal class Program
    {
        public static int ReadValueInt()
        {
            do
            {
                string s = Console.ReadLine();
                if (int.TryParse(s, out int a))
                    return a;
                else
                    Console.WriteLine($"Вы ввели не целое число {s}, введите число правильно");
            }
            while (true);
        }

        static void Main(string[] args)
        {
            Console.WriteLine("Начать работу - любое число кроме -1 выйти из программы - -1");            
            int a = ReadValueInt();
            while (a != -1)
            {
                Console.Clear();
                Console.WriteLine("Введите количество элементов массива");
                int n = 0;
                do
                {
                    if (n < 0)
                        Console.WriteLine("Количество не может быть отрицательным введите заново");
                    n = ReadValueInt();
                }
                while (n < 0);
                var CurrentArray = new Array(n);
                Console.Clear();
                Console.WriteLine("Выберите способ заполнения 1 - ввод с консоли 2 - автоматически");
                a = ReadValueInt();
                switch (a)
                {
                    case 1:
                        CurrentArray.Fill(false);
                    break;
                    case 2:
                        CurrentArray.Fill(true);
                    break;
                }
                while (true) 
                {
                    Console.Clear();
                    CurrentArray.WriteArray();
                    Console.WriteLine("Действия которые можно выполнить с массивом:");
                    Console.WriteLine("-1 Выйти из программы");
                    Console.WriteLine("1 Вставить K элементов в начало");
                    Console.WriteLine("2 Удалить все элементы которые больше среднего арифметического всего массива");
                    Console.WriteLine("3 Циклически сдвинуть на M элементов вправо");
                    Console.WriteLine("4 Найти первый четный");
                    Console.WriteLine("5 Сортировать массив");
                    a = ReadValueInt();
                    if(a == -1)
                        break;
                    switch(a)
                    {
                        case 1:
                            Console.Clear();
                            CurrentArray.WriteArray();
                            Console.WriteLine("Введите количество элементов");
                            do
                            {
                                if(n < 0)
                                    Console.WriteLine("Количество не может быть отрицательным введите заново");
                                n = ReadValueInt();
                            }
                            while (n < 0);
                            Console.WriteLine("Введите " + n.ToString() + " элементов");
                            int[] b = new int[n];   
                            for(int i = 0;i < n;i++)
                                b[i] = ReadValueInt();
                            CurrentArray.Insert(0, new Array(b));
                            CurrentArray.WriteArray();
                            Console.WriteLine("Для продолжения нажмите enter");
                            Console.Read();
                            break;
                        case 2: 
                            Console.Clear();
                            CurrentArray.WriteArray();
                            CurrentArray.DeleteElem(x => x > CurrentArray.Average);
                            CurrentArray.WriteArray();
                            Console.WriteLine("Для продолжения нажмите enter");
                            Console.Read();
                            break;
                        case 3:
                            Console.Clear();
                            CurrentArray.WriteArray();
                            Console.WriteLine("Введите на какое количество нужно сдвинуть");
                            int m = ReadValueInt();
                            CurrentArray.Move(m);
                            CurrentArray.WriteArray();
                            Console.WriteLine("Для продолжения нажмите enter");
                            Console.Read();
                            break;
                        case 4:
                            Console.Clear();
                            CurrentArray.WriteArray();
                            int elem = CurrentArray.FindFirst(x => x % 2 == 0);
                            Console.WriteLine("Первый четный элемент " + elem.ToString());
                            Console.WriteLine("Для продолжения нажмите enter");
                            Console.Read();
                            break;
                        case 5:
                            Console.Clear();
                            CurrentArray.WriteArray();
                            CurrentArray.SortInsets();
                            Console.WriteLine("Отсортированный массив");
                            CurrentArray.WriteArray();
                            
                            Console.WriteLine("любая цифра кроме 1 - продолжить работу 1 - Выполнить бинарный поиск элемента");
                            a = ReadValueInt();
                            if(a == 1)
                            {
                                Console.WriteLine("Введите число которое нужно найти");
                                n = ReadValueInt();
                                var num = CurrentArray.GetIndexBinary(n);
                                if(num != -1)
                                    Console.WriteLine("Ваше число находиться под индексом - " + num.ToString());
                            }
                            
                            Console.WriteLine("Для продолжения нажмите enter");
                            Console.Read();
                            break;

                        default:
                            Console.WriteLine("Вы ввели неправильное a - " + a.ToString() );
                            Console.WriteLine("Для продолжения нажмите enter");
                            Console.Read();
                        break;
                    }

                }
            }
        }
    }
}