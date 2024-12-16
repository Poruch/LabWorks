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
                MyMatrix mat;
                MyTornMatrix mat2;
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
                        mat = new MyMatrix(n, m);
                        Console.WriteLine("Введите 1 если хотите заполнять вручную, введите любое другое число если нет");
                        n = InputManager.ReadValueInt();
                        if(n == 1)
                        mat.Fill(false);
                        else mat.Fill(true);
                        Console.Clear();
                        mat.Write();
                        Console.WriteLine("Введите количество строк");
                        int k = 0;
                        do
                        {
                            if (k < 0)
                                Console.WriteLine("Количество не может быть отрицательным введите заново");
                            k = InputManager.ReadValueInt();
                        }
                        while (k < 0);
                        var result = new MyMatrix(k, m);
                        Console.WriteLine("Введите 1 если хотите заполнять вручную, введите любое другое число если нет");
                        n = InputManager.ReadValueInt();
                        if (n == 1)
                            result.Fill(false);
                        else
                            result.Fill(true);
                        mat.AddRows(result);
                        mat.Write();
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
                        mm.SetBorderRand(1, 10);
                        int pow = InputManager.ReadValueInt();
                        if (pow == 1)
                            mm.Fill(false);
                        else
                            mm.Fill(true);
                        mat2 = new MyTornMatrix(mm.Count, mm.GetData());
                        mat2.Fill();
                        Console.Clear();
                        mat2.Write(2);
                        Console.WriteLine("Введите индекс строки");
                        int ind = 0;
                        do
                        {
                            if (ind < 0)
                                Console.WriteLine("индекс не может быть отрицательным введите заново");
                            ind = InputManager.ReadValueInt();
                        }
                        while (ind < 0);
                        mat2.DeleteElem(ind);
                        mat2.Write(2);
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