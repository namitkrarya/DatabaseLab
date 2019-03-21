EXPLAIN SELECT student_name FROM (Student s INNER JOIN StudentCourse sc ON sc.roll_number = s.roll_number) WHERE sc.course_id = '1' AND
    sc.marks > (SELECT AVG(marks) FROM StudentCourse WHERE StudentCourse.course_id = '2');

CREATE VIEW view1 AS SELECT course_name, roll_number FROM Course c INNER JOIN StudentCourse sc ON sc.course_id = c.course_id;

SELECT * FROM view1 WHERE roll_number = 160101046;

DELIMITER $$
CREATE TRIGGER before_insert_marks BEFORE INSERT ON StudentCourse FOR EACH ROW 
BEGIN 
IF NEW.marks < 0 THEN SET NEW.marks = 0; 
ELSEIF NEW.marks > 100 THEN SET NEW.marks = 100;
END IF;
END $$
DELIMITER ;

ALTER TABLE StudentCourse ADD COLUMN attendance int;

UPDATE StudentCourse SET attendance = rand()*10;


SELECT student_name FROM Student s INNER JOIN StudentCourse sc ON s.roll_number = sc.roll_number AND course_id IN 
(SELECT course_id FROM StudentCourse WHERE roll_number = "160101076") GROUP BY s.roll_number HAVING count(*) =
(SELECT count(course_id) FROM StudentCourse WHERE roll_number = "160101076");

CREATE INDEX roll ON StudentCourse(roll_number);

-- _____________

SELECT * FROM (SELECT student_name FROM Student s INNER JOIN StudentCourse sc ON s.roll_number = sc.roll_number AND course_id IN 
(SELECT course_id FROM StudentCourse WHERE roll_number = "160101076") GROUP BY s.roll_number HAVING count(*) =
(SELECT count(course_id) FROM StudentCourse WHERE roll_number = "160101076")) q WHERE SUBSTRING(student_name, 1, 5) = SUBSTRING((SELECT student_name FROM Student WHERE roll_number = '160101076'), 1, 5);

-- CREATE INDEX name ON Student(student_name(5));

CREATE VIEW grade AS SELECT roll_number, course_id, grade FROM StudentCourse;


ALTER TABLE StudentCourse ADD COLUMN grade varchar(10) DEFAULT 'A';

DELIMITER $$
CREATE TRIGGER before_insert_grade BEFORE INSERT ON StudentCourse FOR EACH ROW 
BEGIN 
IF NEW.marks < 40 THEN SET NEW.grade = 'F'; 
ELSEIF NEW.marks >= 40 AND NEW.marks < 70 THEN SET NEW.grade = 'B';
ELSEIF NEW.marks >=70 THEN SET NEW.grade = 'A';
END IF;
END $$
DELIMITER ;
