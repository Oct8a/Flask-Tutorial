CREATE TABLE tutorial (
	tutorial_id INT GENERATED ALWAYS AS IDENTITY,  
	string VARCHAR NOT NULL,
	date DATE NOT NULL,
	time TIME,
	integer INT CHECK (integer > 0 AND integer < 10),
	numeric NUMERIC(5,2),
	selection VARCHAR(10),
	textarea VARCHAR(500),
	bool BOOLEAN,
	PRIMARY KEY(tutorial_id)
);
