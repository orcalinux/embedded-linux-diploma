from flask import Flask, request, make_response, render_template

app = Flask(__name__, template_folder='templates') # Create a Flask app

@app.route('/') # Define a route
def index():
    value = 'Mahmoud Abdelraouf'
    cal = 50 + 60
    itmes = ['30', '40', '50', '60']
    return render_template('index.html', value=value, cal=cal, items=itmes) # Return a string

@app.route('/hi/<name>') # Define a route with a parameter
def hi(name):
    response = make_response(f'Hello, {name}!\n') # Create a response object
    response.status_code = 200 # 200 OK
    response.headers['Content Types'] = 'Application' # Add a header to the response
    return response

@app.route('/add/<int:num1>/<int:num2>') # Define a route with two parameters
def add(num1, num2):
    return f'The sum is {num1 + num2}\n' # Return a string with the sum of the two parameters

@app.route('/multiply/<float:num1>/<float:num2>') # Define a route with two parameters
def multiply(num1, num2):
    return f'The product is {num1 * num2}\n'

@app.route('/handle_url_params') # Define a route
def handle_url_params():
    # Access URL parameters safely
    if 'name' in request.args and 'age' in request.args:
        name = request.args['name']
        age = request.args['age']
        return f'Name: {name}, Age: {age}'
    else:
        return "Missing 'name' or 'age' parameters!", 400

if __name__ == '__main__': # __name is a special variable that gets the name of the script when it is executed
    app.run(host='localhost', port=5000, debug=True)
