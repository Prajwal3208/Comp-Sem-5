import tkinter as tk
from tkinter import ttk, messagebox
import mysql.connector

def add_stock_to_stocks():
    stock_symbol = stock_symbol_entry.get()
    stock_name = stock_name_entry.get()
    stock_price = float(stock_price_entry.get())

    db = mysql.connector.connect(
        host="localhost",
        user="root",
        password="1401",
        database="inventory"
    )

    cursor = db.cursor()

    try:
        cursor.execute("INSERT INTO stocks (stock_symbol, stock_name, stock_price) VALUES (%s, %s, %s)", (stock_symbol, stock_name, stock_price))
        db.commit()
        messagebox.showinfo("Success", f"Stock {stock_symbol} added to stocks.")
    except Exception as e:
        db.rollback()
        messagebox.showerror("Error", f"Error: {str(e)}")
    finally:
        db.close()

    update_stocks_list()

def view_stocks():
    update_stocks_list()

def update_stocks_list():
    stocks_listbox.delete(0, tk.END)

    db = mysql.connector.connect(
        host="localhost",
        user="root",
        password="1401",
        database="inventory"
    )

    cursor = db.cursor()

    cursor.execute("SELECT stock_id, stock_symbol, stock_name, stock_price FROM stocks")
    stocks = cursor.fetchall()

    for stock_id, symbol, name, price in stocks:
        stocks_listbox.insert(tk.END, f"Stock ID {stock_id}: Symbol: {symbol}, Name: {name}, Price: {price}")

    db.close()

def add_stock_to_inventory():
    stock_id = int(stock_id_entry.get())
    quantity = int(quantity_entry.get())

    db = mysql.connector.connect(
        host="localhost",
        user="root",
        password="1401",
        database="inventory"
    )

    cursor = db.cursor()

    try:
        cursor.execute("SELECT quantity FROM inventory WHERE stock_id = %s", (stock_id,))
        existing_quantity = cursor.fetchone()

        if existing_quantity:
            new_quantity = existing_quantity[0] + quantity
            cursor.execute("UPDATE inventory SET quantity = %s WHERE stock_id = %s", (new_quantity, stock_id))
        else:
            cursor.execute("INSERT INTO inventory (stock_id, quantity) VALUES (%s, %s)", (stock_id, quantity))

        db.commit()
        messagebox.showinfo("Success", f"Stock ID {stock_id} updated in inventory.")
    except Exception as e:
        db.rollback()
        messagebox.showerror("Error", f"Error: {str(e)}")
    finally:
        db.close()

    update_inventory_list()

def remove_stock_from_stocks():
    selected_index = stocks_listbox.curselection()
    if selected_index:
        stock_id = int(stocks_listbox.get(selected_index[0]).split(":")[0].split(" ")[-1])

        db = mysql.connector.connect(
            host="localhost",
            user="root",
            password="1401",
            database="inventory"
        )

        cursor = db.cursor()

        try:
            cursor.execute("DELETE FROM stocks WHERE stock_id = %s", (stock_id,))
            db.commit()
            messagebox.showinfo("Success", f"Stock ID {stock_id} removed from stocks.")
        except Exception as e:
            db.rollback()
            messagebox.showerror("Error", f"Error: {str(e)}")
        finally:
            db.close()

        update_stocks_list()  # Refresh the list


# Function to remove stock from inventory
def remove_stock_from_inventory():
    selected_index = inventory_listbox.curselection()
    if selected_index:
        selected_item = inventory_listbox.get(selected_index[0])
        stock_id_str = None

        # Check if the selected item contains "Stock ID:" and extract the stock ID
        if "Stock ID:" in selected_item:
            parts = selected_item.split("Stock ID:")
            if len(parts) > 1:
                stock_id_str = parts[1].strip().split(",")[0].strip()

        if stock_id_str:
            try:
                stock_id = int(stock_id_str)

                db = mysql.connector.connect(
                    host="localhost",
                    user="root",
                    password="1401",
                    database="inventory"
                )

                cursor = db.cursor()

                try:
                    cursor.execute("DELETE FROM inventory WHERE stock_id = %s", (stock_id,))
                    db.commit()
                    messagebox.showinfo("Success", f"Stock ID {stock_id} removed from inventory.")
                except Exception as e:
                    db.rollback()
                    messagebox.showerror("Error", f"Error: {str(e)}")
                finally:
                    db.close()

                update_inventory_list()
            except ValueError:
                messagebox.showerror("Error", "Invalid stock ID format. Please select a valid stock item.")
        else:
            messagebox.showerror("Error", "Invalid selection. Please select a valid stock item.")


def view_inventory():
    update_inventory_list()

def update_inventory_list():
    inventory_listbox.delete(0, tk.END)

    db = mysql.connector.connect(
        host="localhost",
        user="root",
        password="1401",
        database="inventory"
    )

    cursor = db.cursor()

    cursor.execute("SELECT i.stock_id, i.quantity, s.stock_name, s.stock_price, (i.quantity * s.stock_price) AS total_value FROM inventory i JOIN stocks s ON i.stock_id = s.stock_id")
    stocks = cursor.fetchall()

    for stock_id, quantity, name, price, total_value in stocks:
        inventory_listbox.insert(tk.END, f"Stock ID: {stock_id}, Stock Name: {name}, Quantity: {quantity}, Price: {price}, Value: {total_value:.2f}")

    db.close()


window = tk.Tk()
window.title("Stock Inventory Management")
window.geometry("1000x600")

stocks_frame = ttk.Frame(window, padding=10)
stocks_frame.grid(row=0, column=0, padx=10, pady=10, sticky="nsew")

inventory_frame = ttk.Frame(window, padding=10)
inventory_frame.grid(row=0, column=1, padx=10, pady=10, sticky="nsew")

label_style = ttk.Style()
label_style.configure("Label.TLabel", font=("Arial", 14))

button_style = ttk.Style()
button_style.configure("TButton", font=("Arial", 14))

stock_symbol_label = ttk.Label(stocks_frame, text="Stock Symbol:", style="Label.TLabel")
stock_symbol_label.grid(row=0, column=0, padx=5, pady=5, sticky="e")
stock_symbol_entry = ttk.Entry(stocks_frame, width=20)
stock_symbol_entry.grid(row=0, column=1, padx=5, pady=5)

stock_name_label = ttk.Label(stocks_frame, text="Stock Name:", style="Label.TLabel")
stock_name_label.grid(row=1, column=0, padx=5, pady=5, sticky="e")
stock_name_entry = ttk.Entry(stocks_frame, width=20)
stock_name_entry.grid(row=1, column=1, padx=5, pady=5)

stock_price_label = ttk.Label(stocks_frame, text="Stock Price:", style="Label.TLabel")
stock_price_label.grid(row=2, column=0, padx=5, pady=5, sticky="e")
stock_price_entry = ttk.Entry(stocks_frame, width=20)
stock_price_entry.grid(row=2, column=1, padx=5, pady=5)

add_stock_button = ttk.Button(stocks_frame, text="Add Stock to Stocks", command=add_stock_to_stocks, style="TButton")
add_stock_button.grid(row=3, column=0, columnspan=2, padx=5, pady=10)

remove_stock_button = ttk.Button(stocks_frame, text="Remove Stock from Stocks", command=remove_stock_from_stocks, style="TButton")
remove_stock_button.grid(row=6, column=0, columnspan=2, padx=5, pady=10)

stocks_listbox = tk.Listbox(stocks_frame, width=50, height=10)
stocks_listbox.grid(row=4, column=0, columnspan=2, padx=5, pady=10)

view_stocks_button = ttk.Button(stocks_frame, text="View Stocks", command=view_stocks, style="TButton")
view_stocks_button.grid(row=5, column=0, columnspan=2, padx=5, pady=10)

stock_id_label = ttk.Label(inventory_frame, text="Stock ID:", style="Label.TLabel")
stock_id_label.grid(row=0, column=0, padx=5, pady=5, sticky="e")
stock_id_entry = ttk.Entry(inventory_frame, width=20)
stock_id_entry.grid(row=0, column=1, padx=5, pady=5)

quantity_label = ttk.Label(inventory_frame, text="Quantity:", style="Label.TLabel")
quantity_label.grid(row=1, column=0, padx=5, pady=5, sticky="e")
quantity_entry = ttk.Entry(inventory_frame, width=20)
quantity_entry.grid(row=1, column=1, padx=5, pady=5)

add_stock_to_inventory_button = ttk.Button(inventory_frame, text="Add Stock to Inventory", command=add_stock_to_inventory, style="TButton")
add_stock_to_inventory_button.grid(row=2, column=0, columnspan=2, padx=5, pady=10)

remove_stock_from_inventory_button = ttk.Button(inventory_frame, text="Remove Stock from Inventory", command=remove_stock_from_inventory, style="TButton")
remove_stock_from_inventory_button.grid(row=3, column=0, columnspan=2, padx=5, pady=10)

inventory_listbox = tk.Listbox(inventory_frame, width=50, height=10)
inventory_listbox.grid(row=4, column=0, columnspan=2, padx=5, pady=10)

view_inventory_button = ttk.Button(inventory_frame, text="View Inventory", command=view_inventory, style="TButton")
view_inventory_button.grid(row=5, column=0, columnspan=2, padx=5, pady=10)

window.mainloop()
