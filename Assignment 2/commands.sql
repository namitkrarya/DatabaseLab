INSERT INTO Department VALUES (NULL, 'CSE');
INSERT INTO Department VALUES (NULL, 'BT');
INSERT INTO Department VALUES (NULL, 'MNC');
INSERT INTO Department VALUES (NULL, 'CL');
INSERT INTO Department VALUES (NULL, 'CE');

INSERT INTO Course VALUES ('CS101', '1', '1');
INSERT INTO Course VALUES ('CS102', '1', '2');
INSERT INTO Course VALUES ('CS103', '1', '3');
INSERT INTO Course VALUES ('BT101', '2', '4');
INSERT INTO Course VALUES ('BT102', '2', '5');
INSERT INTO Course VALUES ('MA101', '3', '6');
INSERT INTO Course VALUES ('CH101', '4', '7');
INSERT INTO Course VALUES ('CH102', '4', '8');
INSERT INTO Course VALUES ('ME101', '5', '9');

INSERT INTO Student VALUES ('160101046', 'Namit Kumar', '1');
INSERT INTO Student VALUES ('160101061', 'Saurabh Bazari', '2');
INSERT INTO Student VALUES ('160101036', 'Jatin Goyal', '3');
INSERT INTO Student VALUES ('160101055', 'Ritik Agrawal', '4');
INSERT INTO Student VALUES ('160101076', 'Vivek Raj', '5');
INSERT INTO Student VALUES ('160101043', 'Mohit Singh', '1');
INSERT INTO Student VALUES ('160101059', 'Samyak Jain', '2');

INSERT INTO Teacher VALUES ('R. Inkulu', '1', NULL);
INSERT INTO Teacher VALUES ('Tamuli', '2', NULL);
INSERT INTO Teacher VALUES ('Bikash', '3', NULL);
INSERT INTO Teacher VALUES ('C.K.Jana', '4', NULL);
INSERT INTO Teacher VALUES ('Chandan Mahanta', '5', NULL);

INSERT INTO TeacherCourse VALUES ('1', '3', '1');
INSERT INTO TeacherCourse VALUES ('2', '4', '2');
INSERT INTO TeacherCourse VALUES ('3', '6', '3');
INSERT INTO TeacherCourse VALUES ('4', '7', '4');
INSERT INTO TeacherCourse VALUES ('5', '9', '5');

INSERT INTO StudentCourse VALUES ('160101046', '2');
INSERT INTO StudentCourse VALUES ('160101061', '4');
INSERT INTO StudentCourse VALUES ('160101036', '7');
INSERT INTO StudentCourse VALUES ('160101055', '3');
INSERT INTO StudentCourse VALUES ('160101076', '1');
INSERT INTO StudentCourse VALUES ('160101043', '5');
INSERT INTO StudentCourse VALUES ('160101059', '9');

a SELECT student_name, course_name, Student.roll_number FROM Student, Course, StudentCourse WHERE Course.course_id = StudentCourse.course_id AND Student.roll_number = StudentCourse.roll_number AND Course.course_name = "CS101";

b SELECT student_name, course_name, teacher_name FROM Student, Course, Teacher, StudentCourse, TeacherCourse WHERE Teacher.teacher_id = TeacherCourse.teacher_id AND Course.course_id = TeacherCourse.course_id AND Student.roll_number = StudentCourse.roll_number AND Course.course_id = StudentCourse.course_id AND Teacher.teacher_name = "R. Inkulu";

-- SELECT student_name, course_name FROM Student, Course, TeacherCourse, StudentCourse WHERE Course.course_id = TeacherCourse.course_id AND Course.course_id = StudentCourse.course_id AND Student.roll_number = StudentCourse.roll_number;

c SELECT student_name, course_name FROM Student, Course, StudentCourse WHERE Student.roll_number = StudentCourse.roll_number AND Course.course_id = StudentCourse.course_id AND Student.department_id != Course.department_id AND Student.student_name = "Namit Kumar";

d INSERT INTO StudentCourse VALUES ("160101046", "10", "99");

d INSERT INTO Course VALUES ("CS104", NULL, "1");

e DELETE FROM Course WHERE course_name = "CS101";

f SELECT course_name FROM Student, Course, StudentCourse WHERE Course.course_id = StudentCourse.course_id AND Student.roll_number = StudentCourse.roll_number AND Student.roll_number = "160101046";

g SELECT DISTINCT student_name FROM Student, Course, StudentCourse WHERE Course.course_id IN 
    (SELECT course_id FROM StudentCourse WHERE roll_number = "160101046")
        AND Student.roll_number = StudentCourse.roll_number AND Course.course_id = StudentCourse.course_id;

g SELECT * FROM Student WHERE roll_number IN
    (SELECT roll_number FROM StudentCourse WHERE course_id IN 
        (SELECT course_id FROM StudentCourse WHERE roll_number = "160101046"));

h SELECT DISTINCT course_id FROM StudentCourse WHERE roll_number IN 
    (SELECT roll_number FROM Student WHERE roll_number IN
        (SELECT roll_number FROM StudentCourse WHERE course_id IN
            (SELECT course_id FROM Course WHERE department_id = "1")) AND department_id != "1");

i SELECT roll_number FROM StudentCourse WHERE course_id = "1" AND marks > 91 AND marks < 94;

j INSERT INTO TeacherCourse VALUES ("1", "4", "2");
