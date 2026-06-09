// ── Red-Black Tree ──────────────────────────────────────
const R=0,B=1;
class RBTree{
  constructor(){
    this.nil={d:{id:-1,nome:'nil',tipo:'',valor:0},c:B};
    this.nil.l=this.nil.r=this.nil.p=this.nil;
    this.root=this.nil;
  }
  _lr(x){let y=x.r;x.r=y.l;if(y.l!==this.nil)y.l.p=x;y.p=x.p;if(x.p===this.nil)this.root=y;else if(x===x.p.l)x.p.l=y;else x.p.r=y;y.l=x;x.p=y;}
  _rr(y){let x=y.l;y.l=x.r;if(x.r!==this.nil)x.r.p=y;x.p=y.p;if(y.p===this.nil)this.root=x;else if(y===y.p.r)y.p.r=x;else y.p.l=x;x.r=y;y.p=x;}
  _ifix(z){
    while(z.p.c===R){
      if(z.p===z.p.p.l){let y=z.p.p.r;if(y.c===R){z.p.c=B;y.c=B;z.p.p.c=R;z=z.p.p;}else{if(z===z.p.r){z=z.p;this._lr(z);}z.p.c=B;z.p.p.c=R;this._rr(z.p.p);}}
      else{let y=z.p.p.l;if(y.c===R){z.p.c=B;y.c=B;z.p.p.c=R;z=z.p.p;}else{if(z===z.p.l){z=z.p;this._rr(z);}z.p.c=B;z.p.p.c=R;this._lr(z.p.p);}}
    }
    this.root.c=B;
  }
  insert(item){
    let z={d:{...item},c:R,l:this.nil,r:this.nil,p:this.nil};
    let y=this.nil,x=this.root;
    while(x!==this.nil){y=x;x=z.d.id<x.d.id?x.l:x.r;}
    z.p=y;
    if(y===this.nil)this.root=z;
    else if(z.d.id<y.d.id)y.l=z;else y.r=z;
    this._ifix(z);
  }
  search(id){let x=this.root;while(x!==this.nil){if(id===x.d.id)return x;x=id<x.d.id?x.l:x.r;}return null;}
  _tp(u,v){if(u.p===this.nil)this.root=v;else if(u===u.p.l)u.p.l=v;else u.p.r=v;v.p=u.p;}
  _min(x){while(x.l!==this.nil)x=x.l;return x;}
  _dfix(x){
    while(x!==this.root&&x.c===B){
      if(x===x.p.l){let w=x.p.r;if(w.c===R){w.c=B;x.p.c=R;this._lr(x.p);w=x.p.r;}if(w.l.c===B&&w.r.c===B){w.c=R;x=x.p;}else{if(w.r.c===B){w.l.c=B;w.c=R;this._rr(w);w=x.p.r;}w.c=x.p.c;x.p.c=B;w.r.c=B;this._lr(x.p);x=this.root;}}
      else{let w=x.p.l;if(w.c===R){w.c=B;x.p.c=R;this._rr(x.p);w=x.p.l;}if(w.r.c===B&&w.l.c===B){w.c=R;x=x.p;}else{if(w.l.c===B){w.r.c=B;w.c=R;this._lr(w);w=x.p.l;}w.c=x.p.c;x.p.c=B;w.l.c=B;this._rr(x.p);x=this.root;}}
    }
    x.c=B;
  }
  remove(id){
    let z=this.search(id);if(!z)return;
    let y=z,x,yc=y.c;
    if(z.l===this.nil){x=z.r;this._tp(z,z.r);}
    else if(z.r===this.nil){x=z.l;this._tp(z,z.l);}
    else{y=this._min(z.r);yc=y.c;x=y.r;if(y.p===z)x.p=y;else{this._tp(y,y.r);y.r=z.r;y.r.p=y;}this._tp(z,y);y.l=z.l;y.l.p=y;y.c=z.c;}
    if(yc===B)this._dfix(x);
  }
  inOrder(x,fn){if(x!==this.nil){this.inOrder(x.l,fn);fn(x.d);this.inOrder(x.r,fn);}}
  isEmpty(){return this.root===this.nil;}
  size(x){if(!x||x===this.nil)return 0;return 1+this.size(x.l)+this.size(x.r);}
}

// ── Game Data ────────────────────────────────────────────
const ITEMS=[
  {id:1,nome:'Espada Enferrujada',tipo:'Arma',valor:8},
  {id:3,nome:'Escudo de Madeira',tipo:'Armadura',valor:5},
  {id:5,nome:'Poção Pequena',tipo:'Pocao',valor:25},
  {id:7,nome:'Adaga Afiada',tipo:'Arma',valor:12},
  {id:9,nome:'Armadura de Couro',tipo:'Armadura',valor:9},
  {id:11,nome:'Poção Média',tipo:'Pocao',valor:50},
  {id:13,nome:'Lança de Ferro',tipo:'Arma',valor:18},
  {id:15,nome:'Elmo de Bronze',tipo:'Armadura',valor:12},
  {id:17,nome:'Poção Grande',tipo:'Pocao',valor:99},
  {id:19,nome:'Espada Encantada',tipo:'Arma',valor:25},
  {id:21,nome:'Armadura de Dragão',tipo:'Armadura',valor:20},
  {id:23,nome:'Relíquia Lendária',tipo:'Especial',valor:100},
];
const ENEMIES=[
  {nome:'Goblin',hp:30,atk:8,def:2,exp:20,drop:2},
  {nome:'Lobo Cinzento',hp:40,atk:10,def:3,exp:30,drop:4},
  {nome:'Esqueleto',hp:50,atk:12,def:4,exp:40,drop:0},
  {nome:'Orc Guerreiro',hp:70,atk:15,def:6,exp:60,drop:6},
  {nome:'Troll',hp:90,atk:18,def:8,exp:80,drop:8},
  {nome:'Mago Sombrio',hp:60,atk:22,def:5,exp:90,drop:10},
  {nome:'Dragão Negro',hp:150,atk:28,def:12,exp:150,drop:9},
  {nome:'Guardião Final',hp:200,atk:32,def:15,exp:200,drop:11},
];
const ROOMS=[
  {nome:'Floresta Sombria',desc:'Árvores antigas cercam o caminho. Você ouve passos...',enemies:[0,1],items:[0,2]},
  {nome:'Caverna Úmida',desc:'Gotas ecoam. Ossos cobrem o chão.',enemies:[2,3],items:[1,4]},
  {nome:'Torre em Ruínas',desc:'Magia residual no ar. Pedras desmoronadas.',enemies:[4,5],items:[3,5]},
  {nome:'Covil do Dragão',desc:'Calor intenso. Ouro espalhado. O dragão aguarda.',enemies:[6,7],items:[8,9]},
];

// ── State ────────────────────────────────────────────────
let H={nome:'',hp:100,maxHp:100,atk:15,def:5,lvl:1,exp:0,expNext:100};
let INV=new RBTree();
let room=0,phase='intro';
let aliveEnemies=[],itemsLeft=[],curEnemy=null;

// ── Tree SVG Visualizer ──────────────────────────────────
function drawTree(){
  const svg=document.getElementById('tsvg');
  const W=svg.clientWidth||300,H2=svg.clientHeight||200;
  svg.innerHTML='';
  if(INV.isEmpty()){
    const t=mkSvg('text',{x:W/2,y:H2/2,'text-anchor':'middle',fill:'#444','font-size':13});
    t.textContent='(árvore vazia)';svg.appendChild(t);return;
  }
  // Collect nodes with positions (in-order for x, depth for y)
  const nodes=[],edges=[];
  let order=0;
  function collectInOrder(n,depth){
    if(n===INV.nil)return;
    collectInOrder(n.l,depth+1);
    n._x=order++;n._y=depth;
    nodes.push(n);
    collectInOrder(n.r,depth+1);
  }
  collectInOrder(INV.root,0);
  const maxD=Math.max(...nodes.map(n=>n._y));
  const n=nodes.length;
  const pad=28,r=18;
  const xScale=(W-pad*2)/Math.max(n-1,1);
  const yScale=Math.min((H2-pad*2)/Math.max(maxD,1),55);
  function px(node){return pad+node._x*xScale;}
  function py(node){return pad+node._y*yScale;}
  // Edges
  nodes.forEach(nd=>{
    if(nd.p&&nd.p!==INV.nil&&nd.p.d.id!==-1){
      const ln=mkSvg('line',{x1:px(nd.p),y1:py(nd.p),x2:px(nd),y2:py(nd),stroke:'#333',
        'stroke-width':2});
      svg.appendChild(ln);
    }
  });
  // Nodes
  nodes.forEach(nd=>{
    const cx=px(nd),cy=py(nd);
    const fill=nd.c===R?'#b02020':'#1a1a2e';
    const stroke=nd.c===R?'#e05555':'#555';
    const circ=mkSvg('circle',{cx,cy,r,fill,stroke,'stroke-width':2});
    svg.appendChild(circ);
    const idT=mkSvg('text',{x:cx,y:cy-3,'text-anchor':'middle','dominant-baseline':'middle',
      fill:'#fff','font-size':10,'font-weight':'bold','font-family':'Inter,sans-serif'});
    idT.textContent=nd.d.id;svg.appendChild(idT);
    const nmT=mkSvg('text',{x:cx,y:cy+8,'text-anchor':'middle','dominant-baseline':'middle',
      fill:'#ccc','font-size':7,'font-family':'Inter,sans-serif'});
    nmT.textContent=nd.d.nome.split(' ')[0];svg.appendChild(nmT);
    // Tooltip
    const ti=document.createElementNS('http://www.w3.org/2000/svg','title');
    ti.textContent=`${nd.d.nome}\nID:${nd.d.id} | ${nd.d.tipo} | val:${nd.d.valor}\n${nd.c===R?'🔴 VERMELHO':'⚫ PRETO'}`;
    circ.appendChild(ti);
  });
}
function mkSvg(tag,attrs){
  const el=document.createElementNS('http://www.w3.org/2000/svg',tag);
  Object.entries(attrs).forEach(([k,v])=>el.setAttribute(k,v));
  return el;
}

// ── Logging ──────────────────────────────────────────────
function log(msg,cls='info'){
  const l=document.getElementById('log');if(!l)return;
  const d=document.createElement('div');d.className='msg '+cls;d.innerHTML=msg;
  l.appendChild(d);l.scrollTop=l.scrollHeight;
}
function opLog(msg){
  const ol=document.getElementById('oplog');
  const d=document.createElement('div');d.textContent=`▶ ${msg}`;
  ol.appendChild(d);ol.scrollTop=ol.scrollHeight;
}

// ── Status Panel ─────────────────────────────────────────
function renderStatus(){
  const hp=H.hp,mhp=H.maxHp,exp=H.exp,enxt=H.expNext;
  const items=[];INV.inOrder(INV.root,d=>items.push(d));
  document.getElementById('sbody').innerHTML=`
    <div style="font-family:'Cinzel',serif;font-size:.95rem;color:var(--gold);margin-bottom:8px">${H.nome}</div>
    <div class="stat"><span class="sl">HP</span><span class="sv" style="color:var(--red)">${hp}/${mhp}</span></div>
    <div class="bar-w"><div class="bar hp-b" style="width:${hp/mhp*100}%"></div></div>
    <div class="stat"><span class="sl">Nível</span><span class="sv">${H.lvl}</span></div>
    <div class="stat"><span class="sl">EXP</span><span class="sv">${exp}/${enxt}</span></div>
    <div class="bar-w"><div class="bar exp-b" style="width:${exp/enxt*100}%"></div></div>
    <div class="stat"><span class="sl">ATK</span><span class="sv">${H.atk}</span></div>
    <div class="stat"><span class="sl">DEF</span><span class="sv">${H.def}</span></div>
    <hr style="border:none;border-top:1px solid var(--brd);margin:8px 0">
    <div style="font-size:.68rem;color:var(--dim);letter-spacing:1px;text-transform:uppercase;margin-bottom:5px">Inventário (${INV.size(INV.root)} itens)</div>
    ${items.map(d=>`<div class="inv-it ${d.tipo}" title="${d.tipo} | val:${d.valor}">
      <span style="color:var(--dim)">[${d.id}]</span> ${d.nome} <span style="color:var(--gold);float:right">${d.valor}</span>
    </div>`).join('')}`;
}

// ── Tree Operations ───────────────────────────────────────
function doInsert(item){
  if(INV.search(item.id)){log(`Você já possui ${item.nome}.`,'sys');return;}
  INV.insert(item);
  opLog(`INSERT id=${item.id} "${item.nome}" → insertFixup aplicado`);
  log(`<b>INSERT</b> → <b style="color:var(--gold)">${item.nome}</b> (ID:${item.id}) adicionado à árvore`,'rbt');
  drawTree();renderStatus();
}
function doRemove(id){
  const n=INV.search(id);if(!n)return;
  opLog(`DELETE id=${id} "${n.d.nome}" → transplant + deleteFixup`);
  log(`<b>DELETE</b> → ${n.d.nome} (ID:${id}) removido + rebalanceamento`,'rbt');
  INV.remove(id);drawTree();renderStatus();
}
function doSearch(id){
  const n=INV.search(id);
  opLog(`SEARCH id=${id} → ${n?`encontrado O(log n)`:'não encontrado'}`);
  return n;
}

// ── Game Logic ────────────────────────────────────────────
function startGame(){
  const nm=document.getElementById('pnm').value.trim()||'Herói';
  H={nome:nm,hp:100,maxHp:100,atk:15,def:5,lvl:1,exp:0,expNext:100};
  INV=new RBTree();room=0;phase='room';
  initRoom();
  document.getElementById('isc').style.display='none';
  buildRoomUI();
  doInsert(ITEMS[0]);
}

function initRoom(){
  const r=ROOMS[room];
  aliveEnemies=r.enemies.map(i=>({...ENEMIES[i],maxHp:ENEMIES[i].hp,dropIdx:i}));
  itemsLeft=[...r.items];
}

function buildRoomUI(){
  const r=ROOMS[room];
  const gc=document.getElementById('gc');
  gc.innerHTML=`
    <div class="rhdr"><div class="rnm">⚔ ${r.nome}</div><div class="rds">${r.desc}</div></div>
    <div class="floors">${ROOMS.map((_,i)=>`<div class="fd ${i<room?'done':i===room?'cur':''}"></div>`).join('')}</div>
    <div class="log" id="log"></div>
    <div class="abar" id="abar"></div>`;
  log('Você entra na sala. Fique alerta!','sys');
  renderActions();
}

function renderActions(){
  const bar=document.getElementById('abar');if(!bar)return;
  bar.innerHTML='';
  const alive=aliveEnemies.filter(e=>e.hp>0);
  if(alive.length>0){
    alive.forEach((e,i)=>{mkBtn(bar,`⚔ ${e.nome} (HP:${e.hp})`,()=>startBattle(i),'r');});
  } else {
    itemsLeft.forEach((idx,i)=>{mkBtn(bar,`💎 ${ITEMS[idx].nome}`,()=>pickItem(i));});
    if(room<ROOMS.length-1)mkBtn(bar,'→ Próxima Sala',nextRoom,'gold');
    else mkBtn(bar,'🏆 Vitória!',()=>endGame(true),'gold');
  }
  const pocs=[];INV.inOrder(INV.root,d=>{if(d.tipo==='Pocao')pocs.push(d);});
  pocs.forEach(p=>{mkBtn(bar,`🧪 ${p.nome}`,()=>usePot(p.id),'g');});
  mkBtn(bar,'📋 In-Order',showInv);
}

function mkBtn(parent,txt,fn,cls=''){
  const b=document.createElement('button');
  b.className='btn '+(cls||'');b.textContent=txt;b.onclick=fn;
  parent.appendChild(b);return b;
}

function pickItem(i){
  const item=ITEMS[itemsLeft[i]];
  doInsert(item);
  log(`💎 Coletou: <b style="color:var(--gold)">${item.nome}</b>`,'ok');
  itemsLeft.splice(i,1);renderActions();
}

function usePot(id){
  const n=doSearch(id);if(!n)return;
  const heal=n.d.valor;
  H.hp=Math.min(H.hp+heal,H.maxHp);
  log(`🧪 Usou <b>${n.d.nome}</b> → +${heal} HP (${H.hp}/${H.maxHp})`,'ok');
  doRemove(id);renderStatus();renderActions();
  if(phase==='battle'&&curEnemy)updateEBox();
}

function showInv(){
  const items=[];INV.inOrder(INV.root,d=>items.push(d));
  if(!items.length){log('Inventário vazio.','sys');return;}
  opLog('IN-ORDER: '+items.map(d=>d.id).join(' → '));
  log('<b>IN-ORDER (ID crescente):</b> '+items.map(d=>`<span style="color:var(--gold)">[${d.id}]</span>${d.nome}`).join(' → '),'rbt');
}

function nextRoom(){
  room++;initRoom();buildRoomUI();
  log(`Você avança para: <b style="color:var(--gold)">${ROOMS[room].nome}</b>`,'gold');
}

function startBattle(i){
  curEnemy=aliveEnemies[i];phase='battle';
  log(`<b style="color:var(--red)">⚔ BATALHA: ${H.nome} vs ${curEnemy.nome}!</b>`,'combat');
  const gc=document.getElementById('gc');
  const logEl=document.getElementById('log');
  let eb=document.getElementById('ebox');
  if(!eb){eb=document.createElement('div');eb.id='ebox';eb.className='ebox';gc.insertBefore(eb,logEl);}
  updateEBox();
  const bar=document.getElementById('abar');bar.innerHTML='';
  mkBtn(bar,'⚔ Atacar',attackEnemy,'r');
  const pocs=[];INV.inOrder(INV.root,d=>{if(d.tipo==='Pocao')pocs.push(d);});
  pocs.forEach(p=>{mkBtn(bar,`🧪 ${p.nome}`,()=>{usePot(p.id);refreshBattleBar();});});
  mkBtn(bar,'💨 Fugir',flee);
}

function updateEBox(){
  const e=curEnemy;if(!e)return;
  const pct=Math.max(0,e.hp/e.maxHp*100);
  const eb=document.getElementById('ebox');if(!eb)return;
  eb.innerHTML=`<div class="enm">${e.nome}</div>
    <div class="ehw"><div class="ehb" id="ehb" style="width:${pct}%"></div></div>
    <div class="est">HP: ${Math.max(0,e.hp)}/${e.maxHp} | ATK: ${e.atk} | DEF: ${e.def}</div>`;
}

function refreshBattleBar(){
  const bar=document.getElementById('abar');bar.innerHTML='';
  mkBtn(bar,'⚔ Atacar',attackEnemy,'r');
  const pocs=[];INV.inOrder(INV.root,d=>{if(d.tipo==='Pocao')pocs.push(d);});
  pocs.forEach(p=>{mkBtn(bar,`🧪 ${p.nome}`,()=>{usePot(p.id);refreshBattleBar();});});
  mkBtn(bar,'💨 Fugir',flee);
}

function attackEnemy(){
  const e=curEnemy;
  // Calc ATK bonus from weapons
  let atkBonus=0;INV.inOrder(INV.root,d=>{if(d.tipo==='Arma'&&d.valor>atkBonus)atkBonus=d.valor;});
  let defBonus=0;INV.inOrder(INV.root,d=>{if(d.tipo==='Armadura'&&d.valor>defBonus)defBonus=d.valor;});
  let dmg=Math.max(1,(H.atk+Math.floor(atkBonus/3))-e.def);
  e.hp-=dmg;
  log(`Você causou <b style="color:var(--red)">${dmg} dano</b> a ${e.nome} (${Math.max(0,e.hp)}/${e.maxHp} HP)`,'combat');
  updateEBox();
  if(e.hp<=0){
    log(`<b style="color:var(--grn)">✔ ${e.nome} derrotado!</b>`,'ok');
    gainExp(e.exp);
    // Drop
    const drop=ITEMS[e.dropIdx];
    if(drop){
      log(`💎 ${e.nome} dropou: <b style="color:var(--gold)">${drop.nome}</b>! Coletando...`,'gold');
      setTimeout(()=>{doInsert(drop);},400);
    }
    const eb=document.getElementById('ebox');if(eb)eb.remove();
    phase='room';curEnemy=null;
    renderActions();return;
  }
  // Enemy attacks back
  let eDmg=Math.max(1,e.atk-(H.def+Math.floor(defBonus/3)));
  H.hp-=eDmg;
  log(`${e.nome} causou <b style="color:var(--red)">${eDmg} dano</b> a você (${Math.max(0,H.hp)}/${H.maxHp} HP)`,'combat');
  renderStatus();
  if(H.hp<=0){endGame(false);}
}

function flee(){
  log('Você fugiu da batalha!','sys');
  const eb=document.getElementById('ebox');if(eb)eb.remove();
  phase='room';curEnemy=null;renderActions();
}

function gainExp(exp){
  H.exp+=exp;
  log(`+${exp} EXP`,'gold');
  while(H.exp>=H.expNext){
    H.exp-=H.expNext;H.lvl++;H.maxHp+=20;H.hp=H.maxHp;H.atk+=3;H.def+=2;H.expNext=Math.floor(H.expNext*1.8);
    log(`<b style="color:var(--gold)">★ SUBIU PARA NÍVEL ${H.lvl}! HP:${H.maxHp} ATK:${H.atk} DEF:${H.def}</b>`,'gold');
  }
  renderStatus();
}

function endGame(win){
  phase='end';
  const gc=document.getElementById('gc');
  const items=[];INV.inOrder(INV.root,d=>items.push(d));
  if(win){
    gc.innerHTML=`<div class="intro"><div style="font-family:'Cinzel',serif;font-size:2rem;color:var(--gold);text-shadow:0 0 30px rgba(212,168,83,.7)">🏆 VITÓRIA!</div>
      <div style="font-size:.85rem;color:var(--txt)">${H.nome} recuperou a Relíquia Lendária!</div>
      <div style="font-size:.8rem;color:var(--dim)">Nível ${H.lvl} | HP ${H.hp}/${H.maxHp} | ${items.length} itens</div>
      <div style="font-size:.75rem;color:#9977dd;font-family:monospace;max-width:300px;text-align:left">
        <b>Inventário final (in-order):</b><br>${items.map(d=>`[${d.id}] ${d.nome}`).join('<br>')}
      </div>
      <button class="btn gold" onclick="location.reload()">↺ Jogar Novamente</button></div>`;
  } else {
    gc.innerHTML=`<div class="intro"><div style="font-family:'Cinzel',serif;font-size:2rem;color:var(--red);text-shadow:0 0 30px rgba(200,50,50,.7)">☠ GAME OVER</div>
      <div style="font-size:.85rem;color:var(--dim)">Você foi derrotado...</div>
      <button class="btn r" onclick="location.reload()">↺ Tentar Novamente</button></div>`;
  }
  drawTree();
}

// ── Init ─────────────────────────────────────────────────
window.addEventListener('resize',drawTree);
drawTree();
