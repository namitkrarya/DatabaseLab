-- 1
SELECT * FROM Student WHERE roll_number IN
    (SELECT roll_number FROM StudentCourse WHERE course_id IN    
        (SELECT course_id FROM Course WHERE course_id NOT IN
            (SELECT course_id FROM StudentCourse WHERE roll_number = "160101046")));
-- 1
SELECT s.roll_number, s.student_name FROM Student s INNER JOIN StudentCourse sc ON s.roll_number = sc.roll_number WHERE sc.course_id IN
    (SELECT course_id FROM Course WHERE course_id NOT IN
        (SELECT course_id FROM StudentCourse WHERE roll_number = "160101046"));
-- 2
SELECT student_name FROM Student s INNER JOIN StudentCourse sc ON s.roll_number = sc.roll_number AND course_id IN 
(SELECT course_id FROM StudentCourse WHERE roll_number = "160101076") GROUP BY s.roll_number HAVING count(*) =
(SELECT count(course_id) FROM StudentCourse WHERE roll_number = "160101076");
-- 3
SELECT DISTINCT student_name FROM Student s INNER JOIN StudentCourse sc ON s.roll_number = sc.roll_number WHERE sc.course_id IN
    (SELECT course_id FROM TeacherCourse WHERE teacher_id = '1' OR teacher_id = '2');
-- 4
SELECT student_name FROM Student s WHERE 
(roll_number IN (SELECT roll_number FROM StudentCourse sc INNER JOIN TeacherCourse tc ON sc.course_id = tc.course_id WHERE teacher_id = '1') AND roll_number NOT IN (SELECT roll_number FROM StudentCourse sc INNER JOIN TeacherCourse tc ON sc.course_id = tc.course_id WHERE teacher_id = '2')) OR
(roll_number IN (SELECT roll_number FROM StudentCourse sc INNER JOIN TeacherCourse tc ON sc.course_id = tc.course_id WHERE teacher_id = '2') AND roll_number NOT IN (SELECT roll_number FROM StudentCourse sc INNER JOIN TeacherCourse tc ON sc.course_id = tc.course_id WHERE teacher_id = '1'));
-- 5
SELECT student_name FROM (Student s INNER JOIN StudentCourse sc ON sc.roll_number = s.roll_number) WHERE sc.course_id = '1' AND
    sc.marks > (SELECT AVG(marks) FROM StudentCourse WHERE StudentCourse.course_id = '2');



-- 6
SELECT department_name, count(*) as teachers FROM Department d INNER JOIN Teacher t ON t.department_id = d.department_id GROUP BY d.department_id;
-- 7
SELECT student_name FROM Student s INNER JOIN StudentCourse sc ON s.roll_number=sc.roll_number WHERE s.roll_number NOT IN
    (SELECT roll_number FROM StudentCourse sc1 INNER JOIN TeacherCourse tc ON sc1.course_id=tc.course_id WHERE teacher_id = '1');

-- SELECT student_name, AVG(marks) FROM Student s INNER JOIN StudentCourse sc ON s.roll_number=sc.roll_number GROUP BY sc.roll_number;
-- 8
SELECT department_name, course_name, AVG(marks) FROM Course c INNER JOIN Department d ON d.department_id=c.department_id
    INNER JOIN StudentCourse sc ON sc.course_id=c.course_id GROUP BY c.course_id, d.department_id;

-- 9
SELECT d11.department_name, d12.cname FROM
    (SELECT d1.department_name, MAX(marks) as marks  FROM (SELECT department_name,c.course_name as cname, AVG(marks) as marks FROM Course c INNER JOIN Department d ON d.department_id=c.department_id 
    INNER JOIN StudentCourse sc ON sc.course_id=c.course_id GROUP BY d.department_id, c.course_id) d1 INNER JOIN Department d ON d.department_name=d1.department_name GROUP BY d1.department_name) d11
        INNER JOIN 
    (SELECT department_name,c.course_name as cname, AVG(marks) as marks FROM Course c INNER JOIN Department d ON d.department_id=c.department_id 
    INNER JOIN StudentCourse sc ON sc.course_id=c.course_id GROUP BY d.department_id, c.course_id) d12 
    ON d11.department_name=d12.department_name AND d11.marks=d12.marks;

-- 10
SELECT ('F') as grade, count(marks) FROM StudentCourse WHERE course_id = '1' AND marks < 40
UNION
SELECT ('B') as grade, count(marks) FROM StudentCourse WHERE course_id = '1' AND marks >= 40 AND marks < 70
UNION
SELECT ('A') as grade, count(marks) FROM StudentCourse WHERE course_id = '1' AND marks >= 70;