using lab_9;
using MyTypes;

namespace TestProject1
{
    [TestClass]
    public sealed class Test1
    {
        [TestMethod]
        public void TestingCreatingStudentsAndTheirProperties()
        {
            //Arrange
            Student student = new Student();
            Student student2 = new Student("Петя",18,55);
            Student student3 = new Student(student2);
            //Act
            student.Name = "Valera";
            student.Age = -4;
            student.Gpa = 10;
            //Assert

            Assert.Equals(student.Name ,"Valera");
            //Assert.Equals(student.Age, 0);
            //Assert.Equals(student.Gpa, 10);

            //Assert.Equals(student2.Name, "Петя");
            //Assert.Equals(student2.Age, 18);
            //Assert.Equals(student2.Gpa, 10);

            //Assert.Equals(student2, student3);

            //Assert.Equals(Student.countStudents, 3);
        }
    }
}
