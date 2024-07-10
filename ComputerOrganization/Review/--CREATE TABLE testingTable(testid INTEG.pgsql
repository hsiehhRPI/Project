--CREATE TABLE testingTable(testid INTEGER, testName varchar(50), testAddr TEXT);
--INSERT INTO testingTable(testid, testName, testAddr) VALUES (2, 'Mands', 'Filler Words2');
--DELETE FROM testingTable
--WHERE testid = 2;
--INSERT INTO testingTable(testid, testName, testAddr) VALUES (2, 'Mands', 'Filler Words2');
--INSERT INTO testingTable(testid, testName, testAddr) VALUES (3, 'Hands', 'Filler Words3');
--INSERT INTO testingTable(testid, testName, testAddr) VALUES (4, 'Lands', 'Filler Words4');

--INSERT INTO testingTable(testid, testName, testAddr) VALUES (5, 'Salmon', 'Filler Words5');
--INSERT INTO testingTable(testid, testName, testAddr) VALUES (6, 'Trout', 'Filler Words6');
--INSERT INTO testingTable(testid, testName, testAddr) VALUES (7, 'Tuna', 'Filler Words7');
--INSERT INTO testingTable(testid, testName, testAddr) VALUES (8, 'Anchovis', 'Filler Words8');
--REMEMBER TO COMMENT OUT ONCE YOU ADDED THE ENTRIES, OTHERWISE THEY WILL BE ADDED AGAIN
--UPDATE testingTable SET testName ='Sturgeon' WHERE testid =1;
--UPDATE testingTable SET testName ='Bass' WHERE testid =2;
--UPDATE testingTable SET testName ='Eel' WHERE testid =3;
--UPDATE testingTable SET testName ='Barracuda' WHERE testid =4;

--DELETING SALMON. goodbye
--DELETE FROM testingTable WHERE testid =5;
--INSERT INTO testingTable(testid, testName, testAddr) VALUES (5, 'Salmon', 'Filler Words5');

--INSERT INTO testingTable(testid, testName, testAddr) VALUES (9, 'Silverside', 'Filler Words9');
--UPDATE testingTable SET salary = 2200 WHERE testid = 9;
--UPDATE testingTable SET age = 25 WHERE testid = 9;
--INSERT INTO testingTable(testid, testName, testAddr, age, salary) VALUES (10, 'Mackerel', 'Filler Words10', 30, 2900);
--INSERT INTO testingTable(testid, testName, testAddr, age, salary) VALUES (11, 'Albacore', 'Filler Words11', 32, 4500);
--INSERT INTO testingTable(testid, testName, testAddr, age, salary) VALUES (12, 'Bonito', 'Filler Words12', 26, 2600);
--INSERT INTO testingTable(testid, testName, testAddr, age, salary) VALUES (13, 'Marlin', 'Filler Words13', 29, 3500);
--INSERT INTO testingTable(testid, testName, testAddr, age, salary) VALUES (14, 'Pompano', 'Filler Words14', 22, 1900);
--INSERT INTO testingTable(testid, testName, testAddr, age, salary) VALUES (15, 'Perch', 'Filler Words15', 29, 3500);
--INSERT INTO testingTable(testid, testName, testAddr, age, salary) VALUES (16, 'Carp', 'Filler Words16', 37, 6800);
--INSERT INTO testingTable(testid, testName, testAddr, age, salary) VALUES (17, 'Tarpon', 'Filler Words17', 34, 4000);


SELECT * FROM testingTable ORDER BY testid DESC;

--CODE FOR COWATCH DATABASE
--CREATE TABLE userDatabase {
--  "EMAIL" varchar(100) NOT NULL,
--  "USERNAME" varchar(100) NOT NULL,
-- 
--}