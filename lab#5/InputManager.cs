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
    }
}
