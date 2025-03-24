# **This is just test repository**
nothing interesting here as it stands

---

# **Quick setup**
```bash
# generate ssh key pair with one of two following methods
ssh-keygen -t ed25519 -C "username@example.com"
ssh-keygen -t rsa -b 4096 -C "username@example.com"

# specify location and passphrase
# `key` and `key.pub` are chosen here

# set permissions to the keys
chmod 700 key key.pub

# launch ssh agent in background and add private key to it
eval "$(ssh-agent -s)"
ssh-add key

# copy public key to GitHub
cat key.pub

# test connection and clone your repository
ssh -T git@github.com
git clone "git@github.com:username/repository.git"
```
