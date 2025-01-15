import yaml

cfgpath = 'config/config.yml'
global coding, stdHeight, tcpPort, serverHost, img_dir_local

with open(cfgpath, 'r') as f:
    cfg = yaml.safe_load(f) 
    
    coding = cfg['coding']
    stdHeight = cfg['stdHeight']
    tcpPort = cfg['tcpPort']
    serverHost = cfg['serverHost']
    img_dir_local = cfg['imgLocal']
f.close()