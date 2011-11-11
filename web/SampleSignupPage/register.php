        <?php
		include('config/config.php');
           session_start();
           function reg()
           {
                  // if user already create an account on this session
                  if($_SERVER['REQUEST_METHOD'] == "POST")
                  {
                         $connect = mysql_connect($conf["host"],$conf["user"],$conf["password"]) or die(mysql_error());
                         mysql_select_db($conf["db"],$connect) or die(mysql_error());
                  
                         // get login, password, email from form
                         $login = !get_magic_quotes_gpc() ? addslashes($_POST['login']) : $_POST['login'];
                         $password = !get_magic_quotes_gpc() ? addslashes($_POST['password']) : $_POST['password'];
                         $email = !get_magic_quotes_gpc() ? addslashes($_POST['email']) : $_POST['email'];
                         $ip = $_SERVER['REMOTE_ADDR'];
                         // comment the 2 next line if you allow multi accounts
                         if(($_SESSION['reg'] || already_reg($ip)) && !$conf["multi"])
                                return "<div style='background-color:red; color:white; font-weight:bold;'>Already one accounts on this IP !</div>".form();
                                                 
                         // check for valid password and login
                         if(!is_str($login) || !is_str($password) || strlen($login) <= 5 || strlen($password) <= 5)
                                return "<div style='background-color:red; color:white; font-weight:bold;'>Login or password are invalid !</div>".form();
                         // check for valid email
                         if(!is_email($email))
                                return "<div style='background-color:red; color:white; font-weight:bold;'>Invalid email !</div>".form();
                         // create a new var for encrypted_password
                         $sha1pass = sha1(strtoupper($login).":".strtoupper($password));
                         // if query return true its ok else nok and print again the form
                         $sql = "INSERT INTO accounts(login,password,encrypted_password,gm,email,flags,lastip) VALUES('$login','$password','$sha1pass',0,'$email',24,'$ip');";
                         if(mysql_query($sql))
                         {
                                mysql_close($connect);   
                                $_SESSION['reg'] = true;
                                return "<div style='background-color:green; color:white; font-weight:bold;'>".$conf["ok"]."</div>";
                         }
                         switch(mysql_errno())
                         {
                                case 1062 :
                                   return "<div style='background-color:red; color:white; font-weight:bold;'>This accounts already exist !</div> ".form();
                                   break;
                         }
                         return "Mysql Error : ".mysql_errno()."<br />".form();
                  }
                  else
                         return form();
           }
           function is_str($str)
           {
                  return ereg("^[A-Za-z0-9]+$",$str);
           }
           function is_email($mail)
           {
                         $regex='#^[\w.-]+@[\w.-]+\.[a-zA-Z]{2,5}$#';
                  if(preg_match($regex,$mail));
                  {
                         $c = mysql_query("SELECT email FROM accounts WHERE email = '$mail';");
                         if(mysql_num_rows($c) == 0)
                                return true;
                  }
                  return false;
           }
           function already_reg($ip)
           {
                  $c = mysql_query("SELECT * FROM accounts WHERE lastip = '$ip';");
                  if(mysql_num_rows($c) == 0)
                         return false;
                  return true;
           }
           function form()
           {
                   return '
                  <form action="'.htmlentities($_SERVER['PHP_SELF']).'" method="post">
                         <table align="center">
                                <tr><td>Login : (6 chars min) </td><td><input name="login" value="" type="text" style="border:1px dashed #FFFFFF; background-color:#CCCCCC;" /></td></tr>
                                <tr><td>Password : (6 chars min) </td><td><input name="password" value="" type="password" style="border:1px dashed #FFFFFF;background-color:#CCCCCC;" /></td></tr>
                                <tr><td>Email : </td><td><input name="email" value="" type="text" style="border:1px dashed #FFFFFF;background-color:#CCCCCC;" /></td></tr>
                                <tr><td colspan="2" align="center"><input type="submit" style="border:1px dashed #FFFFFF;background-color:#CCCCCC;"/></td></tr>
                         </table>
                  </form>';
           }
        ?>
        <!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
        <html xmlns="http://www.w3.org/1999/xhtml">
        <head>
        <meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1" />
        <title>Registration</title>
        </head>

        <body style="background-color:#333333; color:#CCCCCC;" link="white" alink="white" vlink="white">
		<center><h3>Registration</h3></center>
        <?php echo reg(); ?>
		<div align="center" style="vertical-align:bottom"><a href="<?php echo $conf["url"]; ?>">Back to main</a></div>
        </body>
        </html>