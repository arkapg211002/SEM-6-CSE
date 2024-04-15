#### Demonstration of data transmission using FTP and HTTP protocols and network traffic using wireshark or tcpdump

To create your own FTP (File Transfer Protocol) server, you can use various software packages available for different operating systems. Here, I'll outline the general steps to set up an FTP server on Linux using `vsftpd` (Very Secure FTP Daemon), which is a popular choice due to its simplicity and security features. This guide assumes you are using a Linux distribution (such as Ubuntu or CentOS), but similar concepts apply to other platforms with different FTP server software.

### Step 1: Install `vsftpd`

1. Update your package list:
   ```bash
   sudo apt update  # For Ubuntu/Debian
   ```

2. Install `vsftpd`:
   ```bash
   sudo apt install vsftpd  # For Ubuntu/Debian
   ```

### Step 2: Configure `vsftpd`

1. Edit the `vsftpd` configuration file (`/etc/vsftpd.conf`):
   ```bash
   sudo nano /etc/vsftpd.conf
   ```

2. Configure `vsftpd` based on your requirements. Here are some common settings:

   - Enable anonymous FTP (optional):
     ```
     anonymous_enable=YES
     ```
   
   - Disable anonymous FTP (recommended for security):
     ```
     anonymous_enable=NO
     ```

   - Allow local users to login (recommended):
     ```
     local_enable=YES
     ```

   - Set the directory for FTP users (e.g., `/home/ftp`):
     ```
     local_root=/home/ftp
     ```

   - Enable write access for local users (use with caution):
     ```
     write_enable=YES
     ```

   - Allow FTP passive mode for firewall compatibility:
     ```
     pasv_enable=YES
     pasv_min_port=40000
     pasv_max_port=40100
     ```

   - Configure user-specific settings (e.g., limit to specific users):
     ```
     user_config_dir=/etc/vsftpd/user_conf
     ```

   Save and exit (`Ctrl+X`, `Y`, `Enter`).

### Step 3: Create FTP User Accounts (if needed)

1. Create a system user for FTP (e.g., `ftpuser`):
   ```bash
   sudo adduser ftpuser
   ```

2. Set a password for the user:
   ```bash
   sudo passwd ftpuser
   ```

### Step 4: Start and Enable `vsftpd`

1. Start the `vsftpd` service:
   ```bash
   sudo systemctl start vsftpd
   ```

2. Enable `vsftpd` to start on boot:
   ```bash
   sudo systemctl enable vsftpd
   ```

### Step 5: Configure Firewall (if applicable)

If you have a firewall enabled (e.g., `ufw` on Ubuntu), allow FTP traffic on port 21 (and passive mode ports if configured):
   ```bash
   sudo ufw allow 21/tcp
   sudo ufw allow 40000:40100/tcp  # Example for passive mode ports
   ```

### Step 6: Test the FTP Server

1. Use an FTP client (e.g., FileZilla, command-line `ftp`) to connect to your server using the IP address or domain name.

2. Log in with the FTP username and password you created.

3. Upload, download, and manage files using the FTP client.

### Additional Considerations:

- **Security**: Always ensure your FTP server is configured securely. Consider using SSL/TLS encryption for FTP (FTPS) or use SFTP (SSH File Transfer Protocol) for more secure file transfers.
  
- **User Management**: Manage FTP user accounts and permissions carefully to restrict access and prevent unauthorized access.

- **Logging**: Enable logging (`xferlog_enable=YES` in `vsftpd.conf`) to monitor FTP activities.

- **Firewall**: Configure your firewall to allow FTP traffic on the necessary ports.

This guide provides a basic setup for creating an FTP server using `vsftpd`. Depending on your specific requirements and environment, you may need to customize the configuration further. Additionally, consider exploring other FTP server software options based on your preferences and operating system.
