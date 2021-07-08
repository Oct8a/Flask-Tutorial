from flask import Flask, render_template, request
from flask_sqlalchemy import SQLAlchemy
import os

host = os.getenv('POSTGRES_HOST', 'localhost')
database = os.getenv('POSTGRES_DATABASE', 'Keto')
user = os.getenv('POSTGRES_USER', 'postgres')
password = os.getenv('POSTGRES_PASS', 'abc123')

app = Flask(__name__)
app.debug = True
app.config['SQLALCHEMY_DATABASE_URI'] = f'postgresql://{user}:{password}@{host}/{database}'
app.config['SQLALCHEMY_TRACK_MODIFICATIONS'] = False
db = SQLAlchemy(app) 

def valid(input):
    return None if input == '' else input

class tutorial(db.Model):
    __tablename__ = 'tutorial'
    tutorial_id = db.Column(db.Integer, primary_key = True)
    string = db.Column(db.String())
    date = db.Column(db.Date())
    time = db.Column(db.Time())
    integer = db.Column(db.Integer)
    numeric = db.Column(db.Numeric(5,2))
    selection = db.Column(db.String(15))
    textarea = db.Column(db.String(500))
    bool = db.Column(db.Boolean())

    def __init__(self, string, date, time, integer, numeric, selection, textarea, bool):
        self.string = valid(string)
        self.date = valid(date)
        self.time = valid(time)
        self.integer = valid(integer)
        self.numeric = valid(numeric)
        self.selection = valid(selection)
        self.textarea = valid(textarea)
        self.bool = valid(bool)


@app.route('/')
@app.route('/home')
# @app.route('/cool')
def index():
    return render_template('index.html') 

@app.route('/write', methods=['GET']) 
def write():
    return render_template('write.html')

@app.route('/read', methods=['GET']) 
def read():

    # selection = 'Option 1'
    option_1 = db.session.query(tutorial)
    # option_1 = db.session.query(tutorial).filter_by(selection=selection)
    # option_1 = db.session.query(tutorial).filter_by(selection=selection).first()
    # for i in option_1:
    #     print(i)
    # print(option_1)
    
    # selection = "SELECT * FROM tutorial"
    # # selection = "SELECT * FROM tutorial WHERE selection=\'" + selection + "\'"
    # # selection = "SELECT * FROM tutorial WHERE selection=\'" + selection + "\' LIMIT 1"
    # data_list =  db.engine.execute(selection)
    # for i in data_list:
    #     print(i)

    # width = 9 * 200
    return render_template('read.html', datalist=option_1)

@app.route('/submit', methods=['POST']) 
def submit():

    if request.method == 'POST':
        print(request.form['found'])
        string = request.form['string']
        date = request.form['date']
        time = request.form['time']
        integer = request.form['integer']
        numeric = request.form['numeric']
        selection = request.form['selection']
        textarea = request.form['textarea']
        bool = request.form.getlist('bool')
        bool = False if len(bool) == 0 else True
        db.session.query(tutorial)
        data = tutorial(string, date, time, integer, numeric, selection, textarea, bool)
        db.session.add(data)
        db.session.commit()
        return render_template('index.html', success='success')

    return render_template('index.html')

if __name__ == '__main__':
    app.run()