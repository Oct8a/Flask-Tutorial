CREATE TABLE tutorial (
	tutorial_id INT GENERATED ALWAYS AS IDENTITY,  
	string VARCHAR,
	date DATE,
	time TIME,
	integer INT,
	numeric NUMERIC(5,2),
	selection VARCHAR(10),
	textarea VARCHAR(500),
	bool BOOLEAN,
	PRIMARY KEY(tutorial_id)
);
