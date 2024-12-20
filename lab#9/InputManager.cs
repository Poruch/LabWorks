using lab_9;
using MyTypes;
using System;
using System.Threading;

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

        public delegate bool AddParam(int a);
        public static int ReadValueUInt(AddParam param,string mesage)
        {
            do
            {
                string s = Console.ReadLine();
                if (int.TryParse(s, out int a) && a >= 0)
                    if (param(a))
                        return a;
                    else
                        Console.WriteLine(mesage);
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
                    Console.WriteLine($"Вы ввели не число {s}, введите число правильно");
            }
            while (true);
        }

        public static Student ReadValueStudent()
        {
            Console.WriteLine("Введите имя, возраст и GPA");
            string s = Console.ReadLine();
            var fields = s.Split(' ');
            int count = fields.Length;
            Student result = new Student();
            int a = 0;
            switch (count)
            {
                case 1:
                    result.Name = fields[0];
                    result.Age += ReadValueUInt();
                    result.Gpa = ReadValueDouble();
                    break;
                case 2:
                    result.Name = fields[0];
                    if (!int.TryParse(fields[1], out a) || a < 0)
                    {
                        Console.WriteLine($"Вы ввели не целое положительное число {fields[1]}, введите его правильно");
                        result.Age += ReadValueUInt();
                    }
                    else
                        result.Age = a;                    
                    result.Gpa = ReadValueDouble();
                    break;
                case 3:
                    result.Name = fields[0];
                    if (!int.TryParse(fields[1], out a) || a < 0)
                    {
                        Console.WriteLine($"Вы ввели не целое положительное число {fields[1]}, введите его правильно");
                        result.Age += ReadValueUInt();
                    }
                    else
                        result.Age = a;
                    if (!double.TryParse(fields[2], out double a2))
                    {
                        Console.WriteLine($"Вы ввели не целое положительное число {fields[2]}, введите его правильно");
                        result.Gpa += ReadValueDouble();
                    }
                    else
                        result.Gpa = a2;
                    break;
            }
            return result; 
        }
    }
}
