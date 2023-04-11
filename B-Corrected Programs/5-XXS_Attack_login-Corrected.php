<!DOCTYPE html>
<html>
<head>
  <meta charset="UTF-8">
  <title>Login Form</title>
  <script src="https://cdn.jsdelivr.net/npm/dompurify@2.2.7/dist/purify.min.js"></script>
</head>
<body>
  <h1>Login Form</h1>
  <form method="POST" action="login.php">
    <label for="username">Username:</label>
    <input type="text" id="username" name="username" required>
    <br>
    <label for="password">Password:</label>
    <input type="password" id="password" name="password" required>
    <br>
    <button type="submit">Login</button>
  </form>
  <script>
    // Sanitize user input using DOMPurify
    const username = document.getElementById('username');
    username.value = DOMPurify.sanitize(username.value);
    const password = document.getElementById('password');
    password.value = DOMPurify.sanitize(password.value);
  </script>
</body>
</html>
