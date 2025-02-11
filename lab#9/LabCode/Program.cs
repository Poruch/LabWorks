﻿using DataManage;
using MyTypes;
using System;
using System.Collections.Generic;
using System.Text;

namespace lab_9
{
    public class Program
    {
        static void Main(string[] args)
        {
            Console.OutputEncoding = Encoding.UTF8;
            Console.WriteLine("Лабораторная #9 ᗜˬᗜ");
            StudentArray studentArray = new StudentArray();
            InputManager.AddParam param = (int n) => { return (studentArray.InBorder(n - 1)); };
            MyInterface.Block studentAction = () =>
            {
                while (MyInterface.Interface(new List<Tuple<string, MyInterface.Block>>()
                    {
                        Tuple.Create<string,MyInterface.Block>("Добавить студента в массив",() => {
                            studentArray.Add(InputManager.ReadValueStudent());
                        }),
                        Tuple.Create<string,MyInterface.Block>("Сравнить двух студентов",() => {
                            Console.WriteLine("Введите два номера студента");
                            int number1 = InputManager.ReadValueUInt(param, "Такого студента нет") - 1;
                            int number2 = InputManager.ReadValueUInt(param, "Такого студента нет") - 1;
                            Console.WriteLine(Student.GetCompare(studentArray[number1],studentArray[number2]));
                        }),
                        Tuple.Create<string,MyInterface.Block>("Нормализовать имена студентов",() => {
                            for (int i = 0; i < studentArray.Count; i++)
                                studentArray[i] = ~studentArray[i];
                            Console.WriteLine(studentArray);
                        }),
                        Tuple.Create<string,MyInterface.Block>("Увеличить возраст студента",() => {
                            Console.WriteLine("Введите номер студента");
                            int number = InputManager.ReadValueUInt(param, "Такого студента нет") - 1;
                            studentArray[number] = studentArray[number]++;
                            Console.WriteLine(studentArray[number].ToString());
                        }),
                        Tuple.Create<string,MyInterface.Block>("Добавить студента со скопированными данными",() => {
                            Console.WriteLine("Введите номер у кого копировать студента");
                            int number = InputManager.ReadValueUInt(param, "Такого студента нет") - 1;
                            Console.WriteLine("Введите имя нового студента");
                            string newName = Console.ReadLine();
                            studentArray.Add(studentArray[number] % newName);
                            Console.WriteLine(studentArray[studentArray.Count - 1].ToString());
                        }),
                        Tuple.Create<string,MyInterface.Block>("Уменьшить GPA студента",() => {
                            Console.WriteLine("Введите номер студента");
                            int number = InputManager.ReadValueUInt(param, "Такого студента нет") - 1;
                            Console.WriteLine("Введите на сколько уменьшить");
                            double d = InputManager.ReadValueDouble();
                            studentArray[number] = studentArray[number] - d;
                            Console.WriteLine(studentArray[number].ToString());
                        }),
                        Tuple.Create<string,MyInterface.Block>("Получить информацию о студенте",() => {
                            Console.WriteLine("Введите номер студента");
                            int number = InputManager.ReadValueUInt((int n) =>
                            {
                                return (studentArray.InBorder(n - 1));
                            }, "Такого студента нет") - 1;
                            Console.WriteLine("Курс студента - " + (int)studentArray[number]);
                            Console.WriteLine("Оценки: " + (studentArray[number] ? "хорошие":"плохие"));
                        }),
                        Tuple.Create<string,MyInterface.Block>("Получить информацию самого старшего студента с GPA > 8",() => {
                            Console.WriteLine(studentArray.GetTHEFIRST().ToString());
                        }),
                        Tuple.Create<string,MyInterface.Block>("Узнать сколько коллекций и сколько студентов",() => {
                            Console.WriteLine("Коллекций - " + StudentArray.countArrays.ToString() + " Количество студентов - " + Student.countStudents.ToString() );
                        }),
                    }))
                {
                    Console.Clear();
                    Console.WriteLine(studentArray);
                }
            };

            while (MyInterface.Interface(new List<Tuple<string, MyInterface.Block>>()
            {
                Tuple.Create<string,MyInterface.Block>("Создать массив студентов",() =>
                {
                    while(MyInterface.Interface(new List<Tuple<string, MyInterface.Block>>()
                    {
                        Tuple.Create<string,MyInterface.Block>("Ввести с консоли", () =>
                        {
                            Console.WriteLine("Введите длину массива");
                            int len = InputManager.ReadValueUInt();
                            for (int i = 0; i < len; i++)
                                studentArray.Add(InputManager.ReadValueStudent());
                            Console.Clear();
                            Console.WriteLine(studentArray);
                            studentAction.Invoke();
                        }),
                        Tuple.Create<string,MyInterface.Block>("Создать из файла", () =>
                        {
                            Console.WriteLine("Введите название файла");
                            do
                                try {
                                    studentArray.Insert(0,InputManager.GetStudentsFromFile("F:\\Вшэ\\LabWorks\\lab#9\\Students.txt"));
                                    break;
                                }
                                catch(Exception e) {
                                    Console.WriteLine(e.Message);
                                }
                            while(true);
                            Console.Clear();
                            Console.WriteLine(studentArray);
                            studentAction.Invoke();
                        }),
                    }))
                    {
                        studentArray.Clear();
                        Console.Clear();
                    }
                }),
            }))
            {
                Console.Clear(); 
            }
        }
    }
}
