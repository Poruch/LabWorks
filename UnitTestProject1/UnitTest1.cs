using Microsoft.VisualStudio.TestTools.UnitTesting;
using MyTypes;


namespace UnitTestProject1
{
    [TestClass]
    public class UnitTest1
    {
        [TestMethod]
        public void TestCreatingStudentsAndTheirProperties()
        {
            //Arrange
            Student student = new Student();
            Student student2 = new Student("Петя", 18, 55);
            Student student3 = new Student(student2);
            //Act
            student.Name = "Valera";
            student.Age = -4;
            student.Gpa = 10;

            //Assert
            Assert.AreEqual(student.Name, "Valera","Not");
            Assert.AreEqual(student.Age, 0);
            Assert.AreEqual(student.Gpa, 10);

            Assert.AreEqual(student2.Name, "Петя");
            Assert.AreEqual(student2.Age, 18);
            Assert.AreEqual(student2.Gpa, 10);

            Assert.AreEqual(student2, student3);

            Assert.AreEqual(Student.countStudents, 3);
        }
    }
}
