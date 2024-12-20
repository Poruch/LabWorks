
using DataManage;
using MyTypes;
using System;
using System.Text;

namespace lab_9
{
    internal class Program
    {//ᗜˬᗜ
        static void Main(string[] args)
        {
            Console.OutputEncoding = Encoding.UTF8;
            Console.WriteLine("Лабораторная #9 ᗜˬᗜ");
            StudentArray studentArray = new StudentArray();
            InputManager.AddParam param = (int n) => { return (studentArray.InBorder(n - 1)); };
            while (MyIntarface.Intarface(new MyCollection<Tuple<string, MyIntarface.Block>>()
            {
                Tuple.Create<string,MyIntarface.Block>("Создать массив студентов",() =>
                {
                    Console.WriteLine("Введите длину массива");
                    int len = InputManager.ReadValueUInt();
                    for (int i = 0; i < len; i++) {
                        studentArray.Add(InputManager.ReadValueStudent());
                    }
                    Console.Clear();
                    studentArray.Write();

                    while (MyIntarface.Intarface(new MyCollection<Tuple<string, MyIntarface.Block>>()
                    {
                        Tuple.Create<string,MyIntarface.Block>("Добавить студента в массив",() => {                            
                            studentArray.Add(InputManager.ReadValueStudent());                            
                        }),
                        Tuple.Create<string,MyIntarface.Block>("Стравнить двух студентов",() => {
                            Console.WriteLine("Введите 2 номера студента");
                            int number1 = InputManager.ReadValueUInt(param, "Такого студента нет") - 1;
                            int number2 = InputManager.ReadValueUInt(param, "Такого студента нет") - 1;
                            Student.WriteCompare(studentArray[number1],studentArray[number2]);
                        }),
                        Tuple.Create<string,MyIntarface.Block>("Нормализовать имена студентов",() => {
                            for (int i = 0; i < len; i++) 
                                studentArray[i] = ~studentArray[i];                            
                        }),
                        Tuple.Create<string,MyIntarface.Block>("Увеличить возраст студента",() => {
                            Console.WriteLine("Введите номер студента");
                            int number = InputManager.ReadValueUInt(param, "Такого студента нет") - 1;
                            studentArray[number] = studentArray[number]++;
                        }),
                        Tuple.Create<string,MyIntarface.Block>("Добавить студента со скопированными данными",() => {
                            Console.WriteLine("Введите номер у кого копировать студента");
                            int number = InputManager.ReadValueUInt(param, "Такого студента нет") - 1;
                            Console.WriteLine("Введите имя нового студента");
                            string newName = Console.ReadLine();
                            studentArray.Add(studentArray[number] % newName);
                        }),
                        Tuple.Create<string,MyIntarface.Block>("Уменьшить GPA студента",() => {
                            Console.WriteLine("Введите номер студента");
                            int number = InputManager.ReadValueUInt(param, "Такого студента нет") - 1;
                            Console.WriteLine("Введите на сколько уменьшить");
                            double d = InputManager.ReadValueDouble();
                            studentArray[number] = studentArray[number] - d;
                        }),
                        Tuple.Create<string,MyIntarface.Block>("Получить информацию о студенте",() => {
                            Console.WriteLine("Введите номер студента");
                            int number = InputManager.ReadValueUInt((int n) =>
                            {
                                return (studentArray.InBorder(n - 1));
                            }, "Такого студента нет") - 1;
                            Console.WriteLine("Курс студента - " + (int)studentArray[number]);
                            Console.WriteLine("Оценки: " + (studentArray[number] ? "хорошие":"плохие"));
                        }),
                        Tuple.Create<string,MyIntarface.Block>("Получить информацию самого старшего студента с GPA > 8",() => {
                            Console.WriteLine(studentArray.GetTHEFIRST().ToString());
                        }),
                    }))
                    {
                        Console.Clear();
                        studentArray.Write();
                    }
                    
                }),
            }))
            {
                Console.Clear(); 
            }

        }
    }
}
