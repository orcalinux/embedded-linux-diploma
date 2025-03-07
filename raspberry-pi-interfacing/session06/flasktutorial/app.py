from flask import Flask, request

app = Flask(__name__)

@app.route('/')
def index():
    return 'Hello, World!'

"""
To test the below route, run the following commands in the terminal:
$ export FLASK_APP=app.py
$ flask run
Then open a web browser and navigate to http://localhost:5000/hi/Mahmoud
"""
@app.route('/hi/<name>')
def greet(name):
    return f'Hello, {name}!'

"""
To test the below route, run the following commands in the terminal:
$ export FLASK_APP=app.py
$ flask run
Then open a web browser and navigate to http://localhost:5000/add/10/5
"""
@app.route('/add/<int:num1>/<int:num2>')
def add(num1, num2):
    return f'The sum is {num1 + num2}'
"""
To test the below route, run the following commands in the terminal:
$ export FLASK_APP=app.py
$ flask run
Then open a web browser and navigate to http://localhost:5000/multiply/5/3
"""
@app.route('/multiply/<int:num1>/<int:num2>')
def multiply(num1, num2):
    return f'The product is {num1 * num2}'

"""
To test the below routes, run the following commands in the terminal:
$ export FLASK_APP=app.py
$ flask run
Then open a web browser and navigate to http://localhost:5000/handle_url_params?name=Mahmoud&age=23
"""
@app.route('/handle_url_params')
# def handle_url_params():
#     return f'URL parameters are {request.args}'
def handle_url_params():
    # Access URL parameters safely
    if 'name' in request.args and 'age' in request.args:
        name = request.args['name']
        age = request.args['age']
        return f'Name: {name}, Age: {age}'
    else:
        return "Missing 'name' or 'age' parameters!", 400
    

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000, debug=True)