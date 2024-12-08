using DataManage;
using MyTypes;
using System;
using System.Linq;

namespace lab_5
{
    internal class Program
    {
        static void Main(string[] args)
        {
            int a = 0;
            do
            {
                Console.Clear();
                Console.WriteLine("Введите что хотите сделать" +
                    "\n1 - добавить K строк в начало," +
                    "\n2 - удалить строку из рваного массива," +
                    "\n3 - выполнить действие со строкой," +
                    "\n-1 - выход из программы");
                a = InputManager.ReadValueInt();
                Matrix mat;
                switch (a)
                {
                    case 1:
                        Console.WriteLine("Введите размеры массива");
                        int n = 0;
                        do
                        {
                            if (n < 0)
                                Console.WriteLine("Количество не может быть отрицательным введите заново");
                            n = InputManager.ReadValueInt();
                        }
                        while (n < 0);
                        int m = 0;
                        do
                        {
                            if (m < 0)
                                Console.WriteLine("Количество не может быть отрицательным введите заново");
                            m = InputManager.ReadValueInt();
                        }
                        while (m < 0);
                        mat = new Matrix(n, m);
                        mat.Fill();
                        Console.Clear();
                        mat.Write(3);
                        Console.WriteLine("Введите количество строк");
                        int k = 0;
                        do
                        {
                            if (k < 0)
                                Console.WriteLine("Количество не может быть отрицательным введите заново");
                            k = InputManager.ReadValueInt();
                        }
                        while (k < 0);
                        for (int i = 0; i < k; i++)
                        {
                            MyDoubleArray arr = new MyDoubleArray(m);
                            arr.Fill();
                            mat.Add(0, arr);
                        }
                        mat.Write(3);
                        Console.WriteLine("Нажмите Enter для продолжения");
                        Console.ReadLine();
                        break;
                    case 2:
                        Console.WriteLine("Введите размеры массива");
                        n = 0;
                        do
                        {
                            if (n < 0)
                                Console.WriteLine("Количество не может быть отрицательным введите заново");
                            n = InputManager.ReadValueInt();
                        }
                        while (n < 0);
                        MyIntArray mm = new MyIntArray(n);
                        Console.WriteLine("Введите 1 если хотите заполнять сами");
                        int pow = InputManager.ReadValueInt();
                        if (pow == 1)
                            mm.Fill(false);
                        else
                            mm.Fill();
                        mat = new Matrix(mm.Count, mm.GetData());
                        mat.Fill();
                        Console.Clear();
                        mat.Write(2);
                        Console.WriteLine("Введите индекс строки");
                        int ind = 0;
                        do
                        {
                            if (ind < 0)
                                Console.WriteLine("индекс не может быть отрицательным введите заново");
                            ind = InputManager.ReadValueInt();
                        }
                        while (ind < 0);
                        mat.DeleteElem(ind);
                        mat.Write(2);
                        Console.WriteLine("Нажмите Enter для продолжения");
                        Console.ReadLine();
                        break;
                    case 3:
                        Console.WriteLine("Введите строку");
                        string buff = Console.ReadLine();
                        MyString s = new MyString(buff);
                        var sentence = s.GetSentence();
                        for (int i = 0; i < sentence.Count; i++)
                        {
                            sentence[i].Write();
                        }
                        Console.WriteLine();
                        Console.WriteLine("Нажмите Enter для продолжения");
                        Console.ReadLine();
                        break;
                    // В лесу родилась елка! В лесу она росла. Зимой и летом была стройная, зеленая!
                    default:
                        break;
                }
            } while (a != -1);
        }
    }
}