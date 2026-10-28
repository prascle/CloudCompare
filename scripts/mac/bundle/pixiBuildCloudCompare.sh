
cd /Users/paul/projets/CloudCompare/CloudCompare
rm -rf .build
ulimit -n 10240
pixi clean
pixi run sign_bundle
