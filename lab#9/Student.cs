using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab_9
{
    internal class Student
    {
        string name;
        int age;
        double gpa;
        public static void Compare(Student s1,Student s2)
        {

        }

        public static Student operator ~(Student s)
        {
            s.name = s.name[0].ToString().ToUpper() + s.name.Substring(1);
            return s;
        }
        public static Student operator ++(Student s)
        {
            s.age++;
            return s;
        }
        public override bool Equals(object obj) 
        {
            return true;
        }
        public static explicit operator int(Student s)
        {             
            return s.age;
        }
        public static implicit operator bool(Student s)
        {
            return s.gpa > 6;
        }

        public static Student operator %(Student s, string newName)
        {
            var result = new Student(s);
            result.name = newName;
            return result;
        }
        public static Student operator -(Student s, double d)
        {
            s.gpa -= d;
            return s;
        }
        public override int GetHashCode() { return 1; }
        public override string ToString() 
        {
            return $"Имя студента: {name}, возраст: {age}, средний бал: {gpa}";
        }
        public Student() { }
        public Student(Student s) 
        {
            gpa = s.gpa;
            name = s.name;
            age = s.age;
        }
        public Student(string name, int age, double gpa) 
        {
            this.name = name;   
            this.age = age;
            this.gpa = gpa;
        }
    }
    

}
