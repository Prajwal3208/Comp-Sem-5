CREATE TABLE library(author varchar2(10), title varchar2(20));

CREATE TABLE library_audit(author varchar2(10), title varchar2(20));

INSERT INTO library VALUES ('A', 'Book1');
INSERT INTO library VALUES ('B', 'Book2');
INSERT INTO library VALUES ('C', 'Book3');
INSERT INTO library VALUES ('D', 'Book4');
INSERT INTO library VALUES ('E', 'Book5');

SELECT * FROM library;

CREATE TRIGGER check_changes
BEFORE UPDATE OR DELETE ON library
FOR EACH ROW
BEGIN
INSERT INTO library_audit VALUES (:old.author, :old.title);
END;
/

UPDATE library SET author='K' where title='Book4';
DELETE FROM library WHERE title='Book2';

SELECT * FROM library;
SELECT * FROM library_audit;
