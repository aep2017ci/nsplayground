# -*- mode: ruby -*-
# vi: set ft=ruby :

VAGRANTFILE_API_VERSION = "2"

Vagrant.configure(VAGRANTFILE_API_VERSION) do |config|
  config.vm.define "nstest", primary: true, autostart: true do |nstest|
    openvz.vm.box = "bento/centos-6.7"

    openvz.vm.hostname = 'nstest.host'
    openvz.vm.network :private_network, ip: "10.254.0.2"
    openvz.vm.synced_folder ".", "/vagrant"

    openvz.vm.provider :virtualbox do |vb|
      vb.gui = false
      vb.name = 'nstest'
      memory = 1024*4
      cpus = 4
      vb.customize ["modifyvm", :id, "--memory", memory, '--cpus', cpus, '--natdnsproxy1', 'off', '--natdnshostresolver1', 'off', '--paravirtprovider', 'kvm']
      vb.customize ["guestproperty", "set", :id, "/VirtualBox/GuestAdd/VBoxService/--timesync-set-threshold", 100]
    end

  end

  config.vm.define "cgtest", autostart: true do |cgtest|
    openvz.vm.box = "ubuntu/trusty64"

    openvz.vm.hostname = 'cgtest.host'
    openvz.vm.network :private_network, ip: "10.254.0.3"
    openvz.vm.synced_folder ".", "/vagrant"

    openvz.vm.provider :virtualbox do |vb|
      vb.gui = false
      vb.name = 'cgtest'
      memory = 1024*4
      cpus = 4
      vb.customize ["modifyvm", :id, "--memory", memory, '--cpus', cpus, '--natdnsproxy1', 'off', '--natdnshostresolver1', 'off', '--paravirtprovider', 'kvm']
      vb.customize ["guestproperty", "set", :id, "/VirtualBox/GuestAdd/VBoxService/--timesync-set-threshold", 100]
    end

  end
end
