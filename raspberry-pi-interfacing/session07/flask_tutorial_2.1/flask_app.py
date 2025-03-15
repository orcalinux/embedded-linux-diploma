from flask import Flask, render_template, request, url_for, redirect

app = Flask(__name__, template_folder='templates')

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/about')
def about():
    return 'My name is Mahmoud Abdelraouf'

@app.route('/hello')
def hello():
    items = ['apple', 'banana', 'cherry']
    return render_template('index.html', items=items)

@app.route('/redirect')
def redirect_():
    return redirect(url_for('hello'))

@app.route('/other')
def form():
    name = request.args.get('name')
    return render_template('other.html', name=name)

# Jinja2 template engine API: https://tedboy.github.io/jinja2/index.html
@app.template_filter('reverse')
def reverse_filter(s):
    return s[::-1]

if __name__ == '__main__':
    app.run(host='0.0.0.0', port = 5000, debug=True)