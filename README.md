# Flask Tutorial
## Description
A small Web Application created with Flask to show how to run a Flask web application, connect to a PostgreSQL database, write to the database using an HTML form, and read from the database to display its results using HTML.

## List of things the tutorial covers:
    Flask:
        1. Installing and Running Flask
        2. Setting Routes
        3. Render HTML Templates
        4. Request Data from HTML Forms
    
    PostgreSQL:
        1. Access & Login to PostgreSQL (Terminal)
        2. Create New Database
        3. Run SQL Queries (Terminal or File)
        4. View Databases & Tables 
    
    SqlAlchemy:
        1. Connect Flask to PostgreSQL
        2. Setup (Class) to Write to DB
        3. Read from PostgreSQL
        4. Write to PostgreSQL

    HTML: 
        1. Create Form(s)
        2. Variety Input Options
        3. Navigating through Routes
        4. Create Web Pages
            a. Home Page
            b. Read Data Page
            c. Write Data Page
            d. Navigation Bar
            e. Footer
            
    Jinja:
        1. Create Links to Routes
        2. Passing Python variables to HTML
        3. Running For and If Statements in HTML
        4. Extending HTML Pages 
        5. Adding Content Blocks

## Dependencies
    Python - Programming Language
    PostgreSQL - A free and open-source relational database management system
    Flask - A micro web framework written in Python
    Psycopg2 - PostgreSQL database adapter for Python
    Psycopg2-binary - PostgreSQL database adapter for Python (Binary Database)
    Flask-sqlalchemy - Extension for Flask that adds support for SQLAlchemy

## Pre-Installation(s):
    Python: https://www.python.org/downloads
    Prosgresql: https://www.postgresql.org/download/

## Installation

    pip install flask
    pip install psycopg2
    pip install psycopg2-binary
    pip install flask-sqlalchemy

## Run

### Debugging Mode
    python app.py

### Production Mode
    Flask run

## PostgreSQL Required Table
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


## PSQL Helpful Commands
    psql -U [username] #Login to PostgreSQL
    CREATE DATABASE [name]; #Create a new database
    \l #List Created Databases
    \c [database] #Connect to Database
    \d #List Tables in Database
    \i path/to/file.sql #Execute SQL queries
    
## Resources
    https://fontawesome.com/download
    https://pixabay.com/
    https://www.w3schools.com/
