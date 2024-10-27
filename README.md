# CarsSelling

**CarsSelling** is a practice project in modern C++ that simulates an interactive car-selling application. Users can choose from a variety of car brands, customize their preferences, and manage purchases through an intuitive menu-driven interface.

### Features

The application offers the following functionalities:

1. Choose car brand
2. Choose car type (Gasoline, Electric, Hybrid)
3. Set a budget
4. Customize car color with an additional cost
5. Add a car to the cart
6. Apply periodic discounts
7. View the car repository
8. Check the shopping cart

---

### How to Run

1. Download or clone this repository.
2. Open and run it in VSCode or another C++ IDE.

---

### Example Output

Here are some examples of typical interactions with the application:

#### Initial Greeting and Main Menu

```
✧✧✧✧✧✧✧✧✧✧✧✧✧✧✧   Dear dear customer! welcome to Yijin's virtual car trade center!   ✧✧✧✧✧✧✧✧✧✧✧✧✧✧✧
✧ You can choose and purchase a car with specific brand, type and color from our factory repertory.
✧ In order to make more $profit$. [Pink], [Gold] and [White] colors are only available for [customizing] | ᴥ•́ )✧
✧ You can always enter 'quit' to [quit] the application and enter '/main' to [return the main menu]. 

Dear customer, what would you like to do? Please choose the corresponding number:
1. Buy
2. Check the repository
3. Check the cart
```

#### Choosing a Car Brand and Type

```
Dear customer, which car brand do you prefer? Please input the corresponding number:
1. BMW
2. Mercedes
3. Tesla
2

What type of Mercedes do you want to buy?
1. Hybrid
2. Gasoline
3. Electric
2
```

#### Setting a Budget

```
Please enter your budget (1€-1000000€):
30000

Sorry, no car satisfies your budget. Try increasing your budget to find more options.

Please enter your budget (1€-1000000€):
80000

1. Mercedes car (ID: 6): Gasoline, Yellow, 53083€
```

#### Customizing Color and Discounts

```
You can now customize the color of this Tesla with an additional cost of 5000€. Would you like to do that?
1. Yes
2. No
```

Upon choosing customization:

```
Please choose the color you would like to customize:
1. Red
2. Blue
3. Green
4. Black
5. Grey
6. Pink
7. Gold
8. White

We've customized your car with the color White.
Car details after customization:
Tesla car (ID: 28): Electric, White, 50401€
```

---

### Special Discount Events

During certain seasons, periodic discounts may apply to specific brands. For example:

```
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
!!!Tesla Discount Season!!!
To appreciate customer support, Tesla has added discounts for selected cars.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
```

---

### Checking the Cart and Finalizing Purchase

```
Dear customer, what would you like to do next? Please choose the corresponding number:
1. Buy
2. Check the repository
3. Check the cart
```

When checking the cart:

```
Cars in your cart:
1. Tesla car (ID: 28): Electric, White, 50401€

Would you like to purchase now or continue shopping?
1. Purchase
2. Continue shopping
```

When exiting the application:

```
Dear customer, thanks for your patronage. Please wait while the application exits...

You have successfully quit the application.
```

---

### Notes

- This program was designed to practice C++ skills, including modern C++ features such as classes, object-oriented programming, and interaction with a user-friendly text-based interface.
- The program showcases basic concepts of inventory management, customizations, and discount systems, useful in e-commerce or retail simulations.






