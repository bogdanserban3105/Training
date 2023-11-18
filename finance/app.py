import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash
import datetime
from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    user_id = session["user_id"]

    transactions_db = db.execute(
        "SELECT symbol, SUM(shares) AS shares, price FROM transactions WHERE user_id = ? GROUP BY symbol", user_id)
    funds_db = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
    funds = funds_db[0]["cash"]

    return render_template("index.html", database=transactions_db, cash=funds)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "GET":
        return render_template("buy.html")
    else:
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        if shares.isdigit():
            shares = int(float(shares))
        else:
            shares = 0
        inventory = lookup(symbol.upper())
        date = datetime.datetime.now()
        user_id = session["user_id"]

        if not symbol:
            return apology("Must provide symbol", 400)
        if not shares:
            return apology("Must provide shares", 400)
        if shares < 0:
            return apology("Share value must be positive", 400)

        inventory = lookup(symbol.upper())

        if inventory == None:
            return apology("Symbol not found", 400)
        if shares == None:
            return apology("Must insert shares", 400)

        price = shares * inventory["price"]

        # Ensure username was submitted
        user_cashdb = db.execute("SELECT cash FROM users WHERE id = :id", id=user_id)
        funds = user_cashdb[0]["cash"]
        # Ensure username was submitted
        if funds < price:
            return apology("Not enouch fonds")
        # Ensure username was submitted
        updated_funds = funds - price
        db.execute("UPDATE users SET cash = ? WHERE id = ?", updated_funds, user_id)
        db.execute("INSERT INTO transactions (user_id, symbol, shares, price, date) VALUES (?, ?, ?, ?, ?)",
                   user_id, inventory["symbol"], shares, inventory["price"], date)
        # Ensure username was submitted
        flash("Transaction Completed!")
        return redirect("/")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    user_id = session["user_id"]
    transactions_db = db.execute("SELECT * FROM transactions WHERE user_id = :id", id=user_id)
    return render_template("history.html", transactions=transactions_db)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "GET":
        return render_template("quote.html")
    else:
        symbol = request.form.get("symbol")

        if not symbol:
            return apology("Must Give Symbol", 400)

        inventory = lookup(symbol.upper())

        if inventory == None:
            return apology("Symbol not found", 400)

        return render_template("quoted.html", name=inventory["name"], price=usd(inventory["price"]), symbol=inventory['symbol'])


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    # Forget any user_id
    session.clear()
    username = request.form.get("username")
    password = request.form.get("password")
    confirm = request.form.get("confirmation")
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "GET":
        return render_template("register.html")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        # Ensure username was submitted

        if not username:
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not password:
            return apology("must provide password", 400)
        elif not confirm:
            return apology("must provide confirmation", 400)
        elif confirm != password:
            return apology("confirm must match password", 400)

        hash = generate_password_hash(password)

        try:
            registered_user = db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, hash)
        except:
            return apology("Username Already Exists", 400)
        session["user_id"] = registered_user

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "GET":
        user_id = session["user_id"]
        symbols_user = db.execute(
            "SELECT symbol FROM transactions WHERE user_id = :id GROUP BY symbol HAVING SUM(shares) > 0 ", id=user_id)
        return render_template("sell.html", symbols=[row["symbol"] for row in symbols_user])

    else:
        symbol = request.form.get("symbol")
        try:
            shares = int(request.form.get("shares"))
        except ValueError:
            return apology("shares must be a posative integer", 400)

        inventory = lookup(symbol.upper())
        date = datetime.datetime.now()

        if not symbol:
            return apology("Must provide symbol", 400)
        if not shares:
            return apology("Must provide shares", 400)
        if shares < 0:
            return apology("You can't sell shares you dont own", 400)

        price = shares * inventory["price"]

        user_id = session["user_id"]
        user_cashdb = db.execute("SELECT cash FROM users WHERE id = :id", id=user_id)
        funds = user_cashdb[0]["cash"]

        updated_funds = funds + price

        user_shares = db.execute(
            "SELECT shares FROM transactions WHERE user_id=:id and symbol = :symbol GROUP BY symbol", id=user_id, symbol=symbol)
        user_shares_remaining = user_shares[0]["shares"]

        if ((shares > user_shares_remaining) or (shares == user_shares_remaining)):
            return apology("You can't sell shares you dont own", 400)

        db.execute("UPDATE users SET cash = ? WHERE id = ?", updated_funds, user_id)
        db.execute("INSERT INTO transactions (user_id, symbol, shares, price, date) VALUES (?, ?, ?, ?, ?)",
                   user_id, inventory["symbol"], (-1)*shares, inventory["price"], date)

        flash("Transaction Completed!")

        return redirect("/")


@app.route("/add", methods=["GET", "POST"])
@login_required
def add():
    """Show add cash of transactions"""

    if request.method == "GET":
        return render_template("add.html")
    else:
        ncash = int(request.form.get("ncash"))

        if not ncash:
            return apology("You must enter a value!", 403)

        user_id = session["user_id"]
        user_cashdb = db.execute("SELECT cash FROM users WHERE id = :id", id=user_id)
        funds = user_cashdb[0]["cash"]

        updated_funds = funds + ncash

        db.execute("UPDATE users SET cash = ? WHERE id = ?", updated_funds, user_id)

        flash("Transaction Completed!")

        return redirect("/")

