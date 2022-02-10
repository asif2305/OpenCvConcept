import pandas as pd
from sklearn.datasets import load_iris
from sklearn.metrics import accuracy_score
import numpy as np
from matplotlib import pyplot as plt

iris = load_iris()

df = pd.DataFrame(iris.data, columns=iris.feature_names)
df['target'] = iris.target

# create one column into another

df['flower_name'] = df.target.apply(lambda x: iris.target_names[x])
df.head()

# data visualization

df0 = df[df.target == 0]
df1 = df[df.target == 1]
df2 = df[df.target == 2]

concat_Data = pd.concat([df0, df1], axis=0)

plt.xlabel('sepal length (cm)')
plt.ylabel('sepal width (cm)')
plt.scatter(df0['sepal length (cm)'], df0['sepal width (cm)'], color='green', marker='+')
plt.scatter(df1['sepal length (cm)'], df1['sepal width (cm)'], color='blue', marker='.')

plt.xlabel('petal length (cm)')
plt.ylabel('petal width (cm)')
plt.scatter(df0['petal length (cm)'], df0['petal width (cm)'], color='green', marker='+')
plt.scatter(df1['petal length (cm)'], df1['petal width (cm)'], color='blue', marker='.')

# train model using sklearn

from sklearn.model_selection import train_test_split

# drop certain colun

X = concat_Data.drop(['petal length (cm)', 'petal width (cm)', 'target', 'flower_name'], axis='columns')

y = concat_Data.target

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2)

from sklearn.svm import SVC

model = SVC(kernel='linear')

model.fit(X_train, y_train)

model.score(X_test, y_test)

y_pred = model.predict(X_test)

print(accuracy_score(y_test, y_pred))

# draw a boundary
import seaborn as sns

plt.figure(figsize=(10, 8))

x_train_data = np.asarray(X_train)
x_train_data = x_train_data[:, :2]
y_train_data = np.asarray(y_train)
y_train_data = y_train_data
y_train_data

# plotting our two-features-space
sns.scatterplot(x=x_train_data[:, 0],
                y=x_train_data[:, 1], hue=y_train, s=30);

# Constructing a hyperline using a formula
w = model.coef_[0]  # w consists of 2 elements
w
b = model.intercept_[0]  # b consists of 1 elements
b

x_points = np.linspace(1, 10)  # generating x-points from -1 and 1
y_points = -(w[0] / w[1]) * x_points - b / w[1]  # getting corresponding y-points

# plotting a red haperplane
plt.plot(x_points, y_points, c='r')

plt.show()
