using MyTypes;
using System;
using System.Diagnostics;
using System.IO;


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
                if (int.TryParse(s, out int a) && a >= 0)
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
                if (int.TryParse(s, out int a) && a > 0)
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
        public static MyCollection<Student> GetStudentsFromFile(string FileName)
        {
            MyCollection<Student> result = new MyCollection<Student>();
            if(!File.Exists(FileName))            
                throw new FileNotFoundException(FileName);
            
            using (StreamReader file = File.OpenText(FileName))
            {
                while (!file.EndOfStream)
                {
                    string line = file.ReadLine();
                    var fields = line.Split('\t');
                    try {
                        result.Add(new Student(fields[0], int.Parse(fields[1]), double.Parse(fields[2])));
                    }
                    catch
                    {
                        Console.WriteLine("Содержимое файла не подходит для извлечения студентов");
                    }
                }               
            }
            return result;
        }
    }
}
