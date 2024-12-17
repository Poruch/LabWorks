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
                        int n = InputManager.ReadValueUInt();
                        int m = InputManager.ReadValueUInt();
                        mat = new MyMatrix(n, m);
                        Console.WriteLine("Введите 1 если хотите заполнять вручную, введите любое другое число если нет");
                        n = InputManager.ReadValueInt();
                        if(n == 1)
                        mat.Fill(false);
                        else mat.Fill(true);
                        Console.Clear();
                        mat.Write();
                        Console.WriteLine("Введите количество строк");
                        int k = InputManager.ReadValueUInt();
                        var result = new MyMatrix(k, m);
                        Console.WriteLine("Введите 1 если хотите заполнять вручную, введите любое другое число если нет");
                        n = InputManager.ReadValueInt();
                        if (n == 1)
                            result.Fill(false);
                        else
                            result.Fill(true);
                        mat.AddRows(result);
                        Console.WriteLine("Результат:");
                        mat.Write();
                        Console.WriteLine("Нажмите Enter для продолжения");
                        Console.ReadLine();
                        break;
                    case 2:
                        Console.WriteLine("Введите размеры массива");
                        n = InputManager.ReadValueUInt();
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
                        Console.WriteLine("Введите номер строки");
                        int ind = InputManager.ReadValueUInt() - 1;
                        mat2.DeleteElem(ind);
                        Console.WriteLine("Результат:");
                        mat2.Write(2);
                        Console.WriteLine("Нажмите Enter для продолжения");
                        Console.ReadLine();
                        break;
                    case 3:
                        Console.WriteLine("Введите строку");
                        string buff = Console.ReadLine();
                        MyString s = new MyString(buff);
                        var sentence = s.GetSentence();
                        Console.WriteLine("Результат:");
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