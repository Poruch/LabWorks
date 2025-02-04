using DataManage;

namespace MyTypes
{
    public class Student
    {
        private string name;
        private int age;
        private double gpa;

        public static int countStudents = 0; 
        public string Name
        {
            get { return name; }
            set
            {
                name = value;
            }
        }
        public int Age
        {
            get { return age; }
            set
            {
                if (value < 0)
                    value = 0;
                age = value;
            }
        }
        public double Gpa
        {
            get { return gpa; }
            set
            {
                gpa = MyMath.Clamp(value, 0, 10);
            }
        }

        public static string GetCompare(Student s1, Student s2)
        {
            string res = "ровесник";
            string res2 = "равен";
            res = s1.Age > s2.Age ? "старше" : res;
            res = s1.Age < s2.Age ? "младше" : res;
            res2 = s1.Gpa > s2.Gpa ? "больше" : res2;
            res2 = s1.Gpa < s2.Gpa ? "меньше" : res2;
            return $"Студент {s1.name} {res} студента {s2.name}\n" + $"GPA студента {s1.name} {res2} GPA студента {s2.name}";
        }

        public static Student operator ~(Student s)
        {
            s.name = s.name[0].ToString().ToUpper() + s.name.Substring(1).ToLower();
            return s;
        }
        public static Student operator ++(Student s)
        {
            s.age++;
            return s;
        }

        public static explicit operator int(Student s)
        {
            int course = s.age - 17;
            if (course < 1 || course > 5)
                return -1;
            return course;
        }
        public static implicit operator bool(Student s)
        {
            return s.Gpa > 6;
        }

        public static Student operator %(Student s, string newName)
        {
            var result = new Student(s);
            result.name = newName;
            return result;
        }
        public static Student operator -(Student s, double d)
        {
            s.Gpa -= d;
            return s;
        }
        public override bool Equals(object obj)
        {
            if (obj is Student student)
                return name == student.name;
            return false;
        }
        public override int GetHashCode()
        {
            int hash = 17;
            hash = hash * 23 + name.GetHashCode();
            hash = hash * 23 + age.GetHashCode();
            hash = hash * 23 + gpa.GetHashCode();
            return 1;
        }
        public override string ToString()
        {
            return $"Имя студента:  {name}, возраст: {age}, средний бал: {gpa}";
        }
        public Student() 
        { 
            countStudents++;
            name = "NoName";
            Age = 0;
            Gpa = 0;
        }
        ~Student() {  countStudents--; }
        public Student(Student s) : this()
        {
            Gpa = s.gpa;
            Name = s.name;
            Age = s.age;
        }
        public Student(string name, int age, double gpa) :this()
        {
            Name = name;
            Age = age;
            Gpa = gpa;
        }
    }


}
