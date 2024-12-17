using System;

namespace DataManage
{

    static class InputManager
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
        public static int ReadValueUInt()
        {
            do
            {
                string s = Console.ReadLine();
                if (int.TryParse(s, out int a) && a > 0)
                    return a;
                else
                    Console.WriteLine($"Вы ввели не целое или целое отрицательное число {s}, введите число правильно");
            }
            while (true);
        }
        public static double ReadValueDouble()
        {
            do
            {
                string s = Console.ReadLine();
                if (double.TryParse(s, out double a))
                    return a;
                else
                    Console.WriteLine($"Вы ввели не целое число {s}, введите число правильно");
            }
            while (true);
        }
    }
}
