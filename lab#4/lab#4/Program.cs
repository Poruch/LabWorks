using System;
using Array;

namespace lab_4
{  

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