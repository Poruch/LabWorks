using System;
using System.Xml.Schema;

namespace MyTypes
{
    internal class StudentArray : MyCollection<Student>
    {
        public StudentArray(MyCollection<Student> collection) : base(collection) { }
        public StudentArray() : base() { }

        public Student GetTHEFIRST()
        {
            var students = FindAll((Student s) => { return s.Gpa > 8; });
            Student THEFIRST = new Student();
            for (int i = 0;i < students.Count; i++)
            {
                if(THEFIRST.Age < students[i].Age)
                    THEFIRST = students[i];
            }
            return THEFIRST;
        }

        public override string ToString()
        {
            string s = "";
            foreach(Student student in this)
            {
                 s += (student.ToString()) + "\n";
            }
            return s;
        }
    }
}
